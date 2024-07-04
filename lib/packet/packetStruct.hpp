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

  enum eTankPacketType : uint8_t
  {
    NET_TANK_PACKET_CHARACTER,
    NET_TANK_PACKET_VARIANT,
    unknown1,
    unknown2,
    NET_TANK_PACKET_WORLD,
    unknown3,
    unknown4,
    unknown5,
    unknown6,
    NET_TANK_PACKET_INVENTORY,
    unknown7,
    unknown8,
    unknown9,
    unknown10,
    unknown11,
    unknown12,
    NET_TANK_PACKET_ITEMS,
    unknown13,
    unknown14,
    unknown15,
    unknown16,
    unknown17,
  };

  struct TankPacketType
  {
    eTankPacketType type;
    uint8_t unk1;
    uint8_t unk2;
    uint8_t unk3;
    uint32_t netID;
    uint32_t unk4;
    uint32_t unk5;
    uint32_t unk6;
    uint32_t unk7;
    float unk8;
    float unk9;
    float unk10;
    float unk11;
    float unk12;
    uint32_t unk13;
    uint32_t unk14;
    uint32_t extended_data_length;
  };
}