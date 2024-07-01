#include "manager/manager.hpp"
#include "connect/connect.hpp"
#include <iostream>

int main()
{
    lib::Manager manager{};
    manager.add_bot("Badjoy", "password");
    return 0;
}