#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include "bot/bot.hpp"

namespace lib
{
    class Manager
    {
    public:
        void add_bot(std::string username, std::string password);

        void remove_bot(std::string username);

        std::shared_ptr<Bot> get_bot(std::string username);

    public:
        std::unordered_map<std::string, std::shared_ptr<Bot>> bots;
        std::shared_ptr<spdlog::logger> logger;
    };
}