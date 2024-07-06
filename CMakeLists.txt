CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(Echo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)
find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/cpr)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/spdlog)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/enet)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/magic_enum)

add_executable(Echo main.cpp lib/connect/connect.cpp lib/manager/manager.cpp lib/bot/bot.cpp lib/packet/packet.cpp)
target_link_libraries(Echo PRIVATE cpr::cpr spdlog::spdlog enet magic_enum::magic_enum ${OPENSSL_LIBRARIES})
