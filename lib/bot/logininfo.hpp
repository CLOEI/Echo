#pragma once

#include <string>

namespace lib
{
  struct LoginInfo
  {
    std::string requestedName;
    int f = 1;
    int protocol = 208;
    float game_version = 4.59;
    int fz = 41750040;
    int lmode = 0;
    int cbits = 1024;
    int player_age = 20;
    int GDPR = 1;
    std::string category = "_-5100";
    int totalPlaytime = 0;
    std::string klv;
    int hash2;
    std::string meta;
    int fhash;
    std::string rid;
    std::string platformID = "0,1,1";
    int deviceVersion = 0;
    std::string country = "us";
    int hash;
    std::string mac;
    std::string wk;
    int zf = 493085170;
  };
}