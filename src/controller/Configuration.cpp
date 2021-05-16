#include "Configuration.h"

Configuration::Configuration() {
  std::ifstream jsonConfigFileStream("resources/txt/config.json", std::ifstream::in);

  if (jsonConfigFileStream.is_open()) {
    jsonConfigFileStream >> configuration_json;
  }
  configuration_json = configuration_json.at("configuration");
  setLogConfig();
  setGameConfig();
}

void Configuration::setGameConfig() {
  this->game = configuration_json.at("game");
  this->sprites = game.at("sprites");

  std::vector<std::string> ec_a;
  for (auto& elem : game["enemies"])
    ec_a.push_back(elem["type"]);

  for (const auto& x : ec_a)
    std::cout << x << "\n";
}

void Configuration::setLogConfig() {
  this->log = configuration_json.at("log");
}

json Configuration::getSprites() {
  return this->sprites;
}
