#include "connect.hpp"
#include "cpr/cpr.h"
#include "enet/enet.h"
#include <string>

void lib::Connect::HTTP() {
  cpr::Response r = cpr::Post(url, cpr::Header{{"User-Agent", "UbiServices_SDK_2022.Release.9_PC64_ansi_static"}, {"Content-Type", "application/x-www-form-urlencoded"}});
  if (r.status_code == 200) {
    parse_server_data(r.text);
  }
}

void lib::Connect::ENET() {
  if (enet_initialize() < 0) {
    return; 
  }

  ENetAddress* address;
  if (enet_address_set_host_ip(address, parsed_server_data["server"].c_str()) != 0) {
    return;
  }
  address->port = std::stoi(parsed_server_data["port"]);

  enet_client = enet_host_create(NULL, 1, 2, 0, 0);
  if (enet_client == nullptr) {
    return;
  }
  enet_peer = enet_host_connect(enet_client, address, 2, 0);
  if (enet_peer == nullptr) {
    return;
  }
}

void lib::Connect::parse_server_data(std::string data) {
  std::string server_data = data;
  std::string delimiter = "\n";
  size_t pos = 0;
  std::string token;
  while ((pos = server_data.find(delimiter)) != std::string::npos) {
    token = server_data.substr(0, pos);
    size_t pos2 = token.find("|");
    std::string key = token.substr(0, pos2);
    std::string value = token.substr(pos2 + 1, token.length());
    parsed_server_data[key] = value;
    server_data.erase(0, pos + delimiter.length());
  }
}