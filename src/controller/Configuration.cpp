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
  this->enemiesCount = game.at("max_enemies");
  this->levels = game.at("levels");
}

void Configuration::setLogConfig() {
  this->log = configuration_json.at("log");
}

json Configuration::getSprites() {
  return this->sprites;
}

int Configuration::getEnemiesCount() {
  return this->enemiesCount;
}

json Configuration::getLevels() {
  return this->levels;
}
