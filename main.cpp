#include "manager/manager.hpp"
#include "connect/connect.hpp"
#include <iostream>

int main()
{
    lib::Manager manager{};
    manager.add_bot("EinstDeath48346", "@Cendy123");
    return 0;
}