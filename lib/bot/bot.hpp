#pragma once

#include "connect/connect.hpp"
#include "logininfo.hpp"
#include <spdlog/spdlog.h>

namespace lib
{
  class Bot : public Connect
  {
  public:
    Bot(std::shared_ptr<spdlog::logger> logger, std::string *username, std::string *password) : Connect(logger)
    {
      this->logger = logger;
      start();
      event();
    }
    void event();

  public:
    bool is_running = false;
    std::shared_ptr<LoginInfo> login_info;
    std::shared_ptr<spdlog::logger> logger;
  };
}