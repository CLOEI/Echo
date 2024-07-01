#include "bot.hpp"
#include <enet/enet.h>
#include <iostream>
#include "utils/random.hpp"
#include "packet/packet.hpp"

void lib::Bot::spoof()
{
  this->login_info.mac = random_mac_address();
  this->login_info.rid = random_hex(32);
  this->login_info.wk = random_hex(32);
}

void lib::Bot::send_packet(packet::ePacketType packet_type, std::string data)
{
  ENetPacket *packet = enet_packet_create(nullptr, sizeof(packet::ePacketType) + data.length(), ENET_PACKET_FLAG_RELIABLE);
  *(packet::ePacketType *)packet->data = packet_type;
  memcpy(packet->data + sizeof(packet::ePacketType), data.c_str(), data.length());

  enet_peer_send(enet_peer, 0, packet);
}

void lib::Bot::event()
{
  ENetEvent event;
  this->is_running = true;
  while (is_running)
  {
    while (enet_host_service(enet_client, &event, 1000) > 0)
    {
      switch (event.type)
      {
      case ENET_EVENT_TYPE_CONNECT:
        logger->info("Connected to the server");
        break;
      case ENET_EVENT_TYPE_RECEIVE:
      {
        lib::packet::Packet pkt(this, &event);
        logger->info("Received {} packet", pkt.name);
        pkt.handle();
        enet_packet_destroy(event.packet);
        break;
      }
      case ENET_EVENT_TYPE_DISCONNECT:
        logger->error("Disconnected from server");
        start();
        break;
      }
    }
  }
}