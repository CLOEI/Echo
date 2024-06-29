#pragma once

#include "connect/connect.hpp"
#include "logininfo.hpp"

namespace lib {
  class Bot: public Connect {
    public:
      LoginInfo* login_info{};
  };
}