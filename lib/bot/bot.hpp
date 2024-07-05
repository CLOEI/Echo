#pragma once

#include "connect/connect.hpp"
#include "logininfo.hpp"
#include <spdlog/spdlog.h>
#include "packet/packetStruct.hpp"

namespace lib
{
  struct SubServer
  {
    std::string ip;
    std::string port;
    std::string token;
    std::string user_id;
    std::string door_id;
    std::string UUID;
  };
  class Bot : public Connect
  {
  public:
    Bot(std::shared_ptr<spdlog::logger> logger, std::string username, std::string password = "") : Connect(logger)
    {
      if (password != "")
      {
        this->login_info.tankIDName = username;
        this->login_info.tankIDPass = password;
      }
      this->login_info.requestedName = username;
      this->logger = logger;
      spoof();
      start();
      event();
    }
    void event();
    void spoof();
    void send_packet(packet::ePacketType packet_type, std::string data);
    void disconnect();

  public:
    bool is_running = false;
    bool is_subserver_redirect = false;
    bool is_ingame = false;
    uint8_t subserver_disconnect_retries = 0;
    SubServer subserver{};
    LoginInfo login_info{};
    std::shared_ptr<spdlog::logger> logger;
  };
}