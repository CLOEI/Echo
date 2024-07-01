#include "bot.hpp"
#include <enet/enet.h>
#include <iostream>

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
        logger->info("Packet type: HELLO");
        break;
      case ENET_EVENT_TYPE_RECEIVE:
        enet_packet_destroy(event.packet);
        break;
      case ENET_EVENT_TYPE_DISCONNECT:
        logger->info("{0} disconnected.", event.peer->address.host);
        start();
        break;
      }
    }
  }
}