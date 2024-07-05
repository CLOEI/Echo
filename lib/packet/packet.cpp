#include "packet.hpp"
#include "packet/packetStruct.hpp"
#include "utils/textparse.hpp"
#include "utils/proton.hpp"
#include "utils/random.hpp"
#include "utils/variant.hpp"
#include <magic_enum.hpp>
#include <iostream>

lib::packet::Packet::Packet(Bot *bot, ENetEvent *event)
{
  this->bot = bot;
  if (event->packet->dataLength < 5)
  {
    return;
  }

  this->type = *(int32_t *)event->packet->data;
  this->data = event->packet->data + 4;
  this->data[event->packet->dataLength - 4] = 0;
  this->name = magic_enum::enum_name(magic_enum::enum_value<ePacketType>(type));

  if (type == NET_MESSAGE_GAME_TANK)
  {
    this->tankPacket = std::make_shared<TankPacketType>();
    memcpy(this->tankPacket.get(), this->data, sizeof(TankPacketType));
  }
}

lib::packet::Packet::~Packet()
{
  if (this->tankPacket)
  {
    this->tankPacket.reset();
  }

  this->bot = nullptr;
}

void lib::packet::Packet::handle_hello()
{
  this->bot->subserver_disconnect_retries = 0;
  utils::TextParse data(fmt::format("requestedName|", this->bot->login_info.requestedName));
  data.add("f", this->bot->login_info.f);
  data.add("protocol", this->bot->login_info.protocol);
  data.add("game_version", this->bot->login_info.game_version);
  data.add("fz", this->bot->login_info.fz);
  data.add("lmode", this->bot->login_info.lmode);
  data.add("cbits", this->bot->login_info.cbits);
  data.add("player_age", this->bot->login_info.player_age);
  data.add("GDPR", this->bot->login_info.GDPR);
  data.add("category", this->bot->login_info.category);
  data.add("totalPlaytime", this->bot->login_info.totalPlaytime);
  this->bot->login_info.klv = utils::proton::generate_klv(stoi(this->bot->login_info.protocol), this->bot->login_info.game_version, this->bot->login_info.rid);
  data.add("klv", this->bot->login_info.klv);
  this->bot->login_info.hash2 = std::to_string(utils::proton::hash_string(fmt::format("{}RT", random_hex(16)).c_str(), 0));
  data.add("hash2", this->bot->login_info.hash2);
  this->bot->login_info.meta = this->bot->parsed_server_data["meta"];
  data.add("meta", this->bot->login_info.meta);
  data.add("fhash", this->bot->login_info.fhash);
  data.add("rid", this->bot->login_info.rid);
  data.add("platformID", this->bot->login_info.platformID);
  data.add("deviceVersion", this->bot->login_info.deviceVersion);
  data.add("country", this->bot->login_info.country);
  this->bot->login_info.hash = std::to_string(utils::proton::hash_string(fmt::format("{}RT", this->bot->login_info.mac).c_str(), 0));
  data.add("hash", this->bot->login_info.hash);
  data.add("mac", this->bot->login_info.mac);
  data.add("wk", this->bot->login_info.wk);
  data.add("zf", this->bot->login_info.zf);

  if (this->bot->is_subserver_redirect)
  {
    data.add("user", this->bot->subserver.user_id);
    data.add("token", this->bot->subserver.token);
    data.add("doorID", this->bot->subserver.door_id);
    data.add("UUIDToken", this->bot->subserver.UUID);
    data.add("lmode", "1");
  }

  if (this->bot->login_info.tankIDName != "")
  {
    data.add("tankIDName", this->bot->login_info.tankIDName);
    data.add("tankIDPass", this->bot->login_info.tankIDPass);
  }

  bot->send_packet(NET_MESSAGE_GENERIC, data.Text + "\n");
}

void lib::packet::Packet::handle_game_message()
{
  auto text = (char *)data;
  std::cout << "Data received: " << text << std::endl;

  if (strstr(text, "action|logon_fail"))
  {
    this->bot->start();
    return;
  }
  if (strstr(text, "requesting that you re-logon"))
  {
    this->bot->start();
    return;
  }
}

void lib::packet::Packet::handle_game_event()
{
  std::cout << "Data received: " << (char *)data << std::endl;
}

void lib::packet::Packet::handle_game_tank()
{
  std::cout
      << "Data received: " << magic_enum::enum_name(magic_enum::enum_value<eTankPacketType>(tankPacket->type)) << std::endl;
  utils::proton::variantlist_t variant;
  variant.serialize_from_mem(this->data + sizeof(TankPacketType));
  std::string function = variant[0].get_string();

  std::cout << "Function: " << function << std::endl;

  if (function == "OnSendToServer")
  {
    if (bot->is_ingame)
    {
      std::cout << "Already in game" << std::endl;
    }
    std::string port = std::to_string(variant[1].get_int32());
    std::string token = std::to_string(variant[2].get_int32());
    std::string user_id = std::to_string(variant[3].get_int32());
    std::string var5 = variant[4].get_string();
    std::vector<std::string> data = utils::TextParse::vectorize(var5);

    bot->is_subserver_redirect = true;
    std::istringstream varStream(var5);
    bot->subserver.ip = data[0];
    bot->subserver.door_id = data[1];
    bot->subserver.UUID = data[2];
    bot->subserver.port = port;
    bot->subserver.token = token;
    bot->subserver.user_id = user_id;
    bot->disconnect();
  }

  if (function == "OnSuperMainStartAcceptLogonHrdxs47254722215a")
  {
    bot->is_ingame = true;
    bot->send_packet(NET_MESSAGE_GENERIC, "action|enter_game\n");
  }
}

void lib::packet::Packet::handle_game_client_log_request()
{
  std::cout << "Data received: " << (char *)data << std::endl;
}

void lib::packet::Packet::handle()
{
  switch (type)
  {
  case NET_MESSAGE_HELLO:
    handle_hello();
    break;
  case NET_MESSAGE_GAME_MESSAGE:
    handle_game_message();
    break;
  case NET_MESSAGE_GAME_EVENT:
    handle_game_event();
    break;
  case NET_MESSAGE_GAME_TANK:
    handle_game_tank();
    break;
  case NET_MESSAGE_CLIENT_LOG_REQUEST:
    handle_game_client_log_request();
    break;
  default:
    break;
  }
}