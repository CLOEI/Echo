#include "connect.hpp"
#include "bot/bot.hpp"
#include "cpr/cpr.h"
#include "enet/enet.h"
#include <iostream>
#include <string>

void lib::Connect::start()
{
    HTTP();
    ENET();
}

void lib::Connect::HTTP()
{
    bool success = false;
    while (!success)
    {
        cpr::Response r = cpr::Post(url, cpr::Header{{"User-Agent", "UbiServices_SDK_2022.Release.9_PC64_ansi_static"},
                                                     {"Content-Type", "application/x-www-form-urlencoded"}});
        if (r.status_code == 200)
        {
            parse_server_data(r.text);
            success = true;
        }
        else
        {
            logger->error("Failed to parse data from server, re-parsing...");
        }
    }
}

void lib::Connect::ENET()
{
    if (enet_initialize() < 0)
    {
        logger->error("Failed to initialize ENET");
        return;
    }

    if (parsed_server_data.find("maint") != parsed_server_data.end())
    {
        logger->error("Server is under maintenance");
        exit(0);
    }

    enet_client = enet_host_create(NULL, 1, 2, 0, 0);
    if (enet_client == nullptr)
    {
        logger->error("Failed to create ENET client");
        return;
    }
    enet_client->usingNewPacket = true;
    enet_client->checksum = enet_crc32;
    enet_host_compress_with_range_coder(enet_client);
    logger->info("Connecting to {}:{}", parsed_server_data["server"], parsed_server_data["port"]);
    ENET_connect(parsed_server_data["server"], parsed_server_data["port"]);
}

void lib::Connect::ENET_connect(std::string ip, std::string port)
{
    // ENetSocks5Config socks5Config;
    // socks5Config.address.port = 1080;
    // if (enet_address_set_host_ip(&socks5Config.address, "127.0.0.1") != 0)
    // {
    //     logger->error("Failed to set socks5 address, restarting...");
    //     start();
    // }

    ENetAddress address;
    if (enet_address_set_host_ip(&address, ip.c_str()) != 0)
    {
        logger->error("Failed to set host ip, restarting...");
        start();
    }
    address.port = std::stoi(port);
    // if (enet_host_use_socks5(enet_client, &socks5Config) != 0)
    // {
    //     logger->error("Failed to use socks5, restarting...");
    //     start();
    // }
    enet_peer = enet_host_connect(enet_client, &address, 2, 0);
    if (enet_peer == nullptr)
    {
        logger->error("Failed to connect to server");
        return;
    }
}

void lib::Connect::parse_server_data(std::string data)
{
    std::string server_data = data;
    std::string delimiter = "\n";
    size_t pos = 0;
    std::string token;
    while ((pos = server_data.find(delimiter)) != std::string::npos)
    {
        token = server_data.substr(0, pos);
        size_t pos2 = token.find("|");
        std::string key = token.substr(0, pos2);
        std::string value = token.substr(pos2 + 1, token.length());
        parsed_server_data[key] = value;
        server_data.erase(0, pos + delimiter.length());
    }
}