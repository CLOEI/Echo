#pragma once

#include <memory>

namespace lib {
  class Manager {
    public:
      void add_bot(std::string username, std::string password);
      void remove_bot(std::string username);
      void get_bot(std::string username);
    public:
      std::shared_ptr<std::string> bots;
  };
}