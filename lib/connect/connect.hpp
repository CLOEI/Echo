#pragma once

#include "cpr/cprtypes.h"
#include "enet/enet.h"
#include <map>
#include <string>
#include <spdlog/spdlog.h>

namespace lib
{
    class Connect
    {
    public:
        Connect(std::shared_ptr<spdlog::logger> logger)
        {
            this->logger = logger;
        }
        void HTTP();

        void ENET();

        void start();

    private:
        void parse_server_data(std::string data);

    public:
        std::shared_ptr<spdlog::logger> logger;
        std::map<std::string, std::string> parsed_server_data;
        cpr::Url url{"https://www.growtopia1.com/growtopia/server_data.php"};
        ENetHost *enet_client;
        ENetPeer *enet_peer;
    };
}