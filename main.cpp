#include "manager/manager.hpp"
#include "connect/connect.hpp"
#include <iostream>

int main()
{
    lib::Manager manager{};
    manager.add_bot("username", "password");
    return 0;
}