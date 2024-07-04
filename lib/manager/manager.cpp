#include "manager.hpp"
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void lib::Manager::add_bot(std::string username, std::string password)
{
  this->logger = spdlog::stdout_color_mt(username);
  logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
  if (password != "")
  {
    logger->info("Adding bot with username: {} and password: {}", username, password);
  }
  else
  {
    logger->info("Adding bot with username: {}", username);
  }
  bots.insert_or_assign(username, std::make_shared<Bot>(logger, username, password));
}

void lib::Manager::remove_bot(std::string username)
{
  logger->info("Removing bot with username: {}", username);
  this->bots.erase(username);
}

std::shared_ptr<lib::Bot> lib::Manager::get_bot(std::string username)
{
  logger->info("Getting bot with username: {}", username);
  return this->bots[username];
}