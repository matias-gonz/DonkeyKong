#include "Configuration.h"

Configuration::Configuration() {
  std::ifstream jsonConfigFileStream("resources/txt/config.json", std::ifstream::in);

  if (jsonConfigFileStream.is_open()) {
    jsonConfigFileStream >> configuration_json;
  }

  if(hasKey(configuration_json, "configuration")) {
    configuration_json = configuration_json.at("configuration");
    this->setLogConfig();
    this->setGameConfig();
  } else {
    this->loadDefaultConfig();
  }
}

void Configuration::setGameConfig() {
  if(hasKey(configuration_json, "game")) {
    this->game = configuration_json.at("game");
    if(hasKey(game, "sprites") && hasKey(game, "probability_enemies") &&
    hasKey(game, "levels")) {
      this->sprites = game.at("sprites");
      this->enemiesCount = game.at("probability_enemies");
      this->levels = game.at("levels");
    } else {
      this->loadDefaultConfig();
    }
  } else {
    this->loadDefaultConfig();
  }
}

void Configuration::loadDefaultConfig() {
  std::ifstream in("resources/txt/default_config.json");
  configuration_json = json::parse(in, nullptr, false);
  if (configuration_json.is_discarded()) { printf("Error al leer el archivo default"); }
  configuration_json = configuration_json.at("configuration");
  this->setLogConfig();
  this->setGameConfig();
  this->loadsDefault = true;
}

void Configuration::setLogConfig() {
  if(hasKey(configuration_json, "log")) {
    this->log = configuration_json.at("log");
  } else {
    this->loadDefaultConfig();
  }
}

json Configuration::getSprites() {
  return this->sprites;
}

int Configuration::getEnemiesCount() {
  return this->enemiesCount;
}

bool Configuration::hasKey(json json, std::string key) {
  auto validJson = json.find(key);
  return (validJson != json.end());
}

json Configuration::getLevels() {
  return this->levels;
}

json Configuration::getLogLevel() {
  return this->log;
}

bool Configuration::isDefault() {
  return this->loadsDefault;
}
