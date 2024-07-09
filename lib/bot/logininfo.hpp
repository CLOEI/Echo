#pragma once

#include <string>

namespace lib
{
    struct LoginInfo
    {
        std::string tankIDName;
        std::string tankIDPass;
        std::string requestedName;
        std::string f = "1";
        std::string protocol = "208";
        std::string game_version = "4.61";
        std::string fz = "41750040";
        std::string lmode = "0";
        std::string cbits = "1024";
        std::string player_age = "20";
        std::string GDPR = "1";
        std::string category = "_-5100";
        std::string totalPlaytime = "0";
        std::string klv;
        std::string hash2;
        std::string meta;
        std::string fhash = "-716928004";
        std::string rid;
        std::string platformID = "0,1,1";
        std::string deviceVersion = "0";
        std::string country = "us";
        std::string hash;
        std::string mac;
        std::string wk;
        std::string zf = "493085170";
    };
}