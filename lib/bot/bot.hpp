#pragma once

#include "connect/connect.hpp"
#include "logininfo.hpp"
#include <spdlog/spdlog.h>
#include "packet/packetStruct.hpp"

namespace lib
{
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

  public:
    bool is_running = false;
    LoginInfo login_info{};
    std::shared_ptr<spdlog::logger> logger;
  };
}