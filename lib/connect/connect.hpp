#pragma once

#include "cpr/cprtypes.h"
#include "enet/enet.h"
#include <map>
#include <string>

namespace lib {
  class Connect {
    public:
      void HTTP();
      void ENET();
    private:
      void parse_server_data(std::string data);
    public:
      std::map<std::string, std::string> parsed_server_data;
      cpr::Url url{"https://www.growtopia1.com/growtopia/server_data.php"};
      ENetHost* enet_client;
      ENetPeer* enet_peer;
  };
}