CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(Echo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/cpr)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/spdlog)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/enet-socks5/enet)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/magic_enum)

add_executable(Echo main.cpp lib/connect/connect.cpp lib/manager/manager.cpp
        lib/utils/hash.hpp
        lib/utils/random.hpp
        lib/utils/proton.hpp)
target_link_libraries(Echo PRIVATE cpr::cpr spdlog::spdlog enet magic_enum::magic_enum)
