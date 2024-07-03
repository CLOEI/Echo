#pragma once

#include "bot/bot.hpp"
#include <enet/enet.h>

namespace lib::packet
{
  class Packet
  {
  public:
    Packet(Bot *bot, ENetEvent *event);
    void handle();

  private:
    void handle_hello();
    void handle_game_message();
    void handle_game_event();
    void handle_game_tank();

  private:
    uint32_t type;
    uint8_t *data;

  public:
    Bot *bot;
    std::string name;
  };
}