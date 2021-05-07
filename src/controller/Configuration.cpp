#include "Configuration.h"

Configuration::Configuration() {
  std::ifstream jsonConfigFileStream("resources/txt/config.json", std::ifstream::in);

  if (jsonConfigFileStream.is_open()) {
    jsonConfigFileStream >> configuration_json;
  }
  configuration_json = configuration_json.at("configuration");
  setLogConfig(configuration_json);
  setGameConfig(configuration_json);
}

void Configuration::setGameConfig(json &game_json) {
  this->game = configuration_json.at("game");
}

void Configuration::setLogConfig(json &log_json) {
  this->log = configuration_json.at("log");;
}
