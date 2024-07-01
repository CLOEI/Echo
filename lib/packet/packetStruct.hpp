#pragma once

#include <cstdint>

namespace lib::packet
{
  enum ePacketType : uint32_t
  {
    NET_MESSAGE_UNKNOWN,
    NET_MESSAGE_HELLO,
    NET_MESSAGE_GENERIC,
    NET_MESSAGE_GAME_MESSAGE,
    NET_MESSAGE_GAME_TANK,
    NET_MESSAGE_PACKET_FIVE,
    NET_MESSAGE_GAME_EVENT,
  };
}