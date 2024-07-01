#pragma once

#include <string>
#include <array>
#include "hash.hpp"

namespace utils::proton
{
    std::string generate_klv(const int protocol, const std::string &version, const std::string &rid)
    {
        constexpr std::array salts = {
            "e9fc40ec08f9ea6393f59c65e37f750aacddf68490c4f92d0d2523a5bc02ea63",
            "c85df9056ee603b849a93e1ebab5dd5f66e1fb8b2f4a8caef8d13b9f9e013fa4",
            "3ca373dffbf463bb337e0fd768a2f395b8e417475438916506c721551f32038d",
            "73eff5914c61a20a71ada81a6fc7780700fb1c0285659b4899bc172a24c14fc1"};

        static std::array constant_values = {
            hash::sha256(hash::md5(hash::sha256(std::to_string(protocol)))),
            hash::sha256(hash::sha256(version)),
            hash::sha256(hash::sha256(std::to_string(protocol)) + salts[3])};

        return hash::sha256(constant_values[0] + salts[0] + constant_values[1] + salts[1] + hash::sha256(hash::md5(hash::sha256(rid))) + salts[2] + constant_values[2]);
    }

    uint32_t hash_string(const char *str, int32_t len)
    {
        if (!str)
            return 0;

        auto *n = (unsigned char *)str;
        uint32_t acc = 0x55555555;

        if (len == 0)
        {
            while (*n)
                acc = (acc >> 27) + (acc << 5) + *n++;
        }
        else
        {
            for (int32_t i = 0; i < len; i++)
            {
                acc = (acc >> 27) + (acc << 5) + *n++;
            }
        }
        return acc;
    }
}