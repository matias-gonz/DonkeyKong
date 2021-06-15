#include "Configuration.h"

Configuration::Configuration() {
  std::ifstream jsonConfigFileStream("resources/txt/config.json", std::ifstream::in);

  if (jsonConfigFileStream.is_open()) {
    jsonConfigFileStream >> configuration_json;
  }

  if (hasKey(configuration_json, "configuration")) {
    configuration_json = configuration_json.at("configuration");
    this->setLogConfig();
    this->setGameConfig();
  } else {
    this->loadDefaultConfig();
  }
}

void Configuration::setGameConfig() {
  if (hasKey(configuration_json, "game")) {
    this->game = configuration_json.at("game");
    if (hasKey(game, "sprites") && hasKey(game, "probability_enemies") &&
        hasKey(game, "levels") && hasKey(game, "users") && hasKey(game, "user_count")) {
      this->sprites = game.at("sprites");
      this->enemiesCount = game.at("probability_enemies");
      this->levels = game.at("levels");
      // this->userCount = game.at("user_count");
      for (auto &td: game.at("users")) {
        this->user.username = td["user"];
        this->user.password = td["password"];
        this->users.push_back(user);
      }
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
  if (hasKey(configuration_json, "log")) {
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

bool Configuration::checkCredentials(std::string *inputUser, std::string *inputPass) {
  bool found = false;
  this->user.username = *inputUser;
  this->user.password = *inputPass;
  for (int i = 0; i < this->users.size(); i++) {
    if (users[i].username == *inputUser && users[i].password == *inputPass) {
      found = true;
      this->changeToActiveUser(inputUser, inputPass);
    }
  }
  return found;
}

void Configuration::changeToActiveUser(std::string *inputUser, std::string *inputPass) {
  int index;
  for (int i = 0; i < this->users.size(); i++) {
    if (users[i].username == *inputUser && users[i].password == *inputPass) {
      index = i;
      this->activeUsers.push_back(this->users[i]);
    }
  }
  for (int i = index; i < this->users.size() - 1; i++) this->users[i] = this->users[i + 1];

}