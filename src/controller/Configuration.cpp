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
    if(hasKey(game, "sprites") && hasKey(game, "probability_enemies")&& hasKey(game, "hammer_count") &&
    hasKey(game, "levels") && hasKey(game, "users") && hasKey(game, "client_max")) {
      this->sprites = game.at("sprites");
      this->enemiesCount = game.at("probability_enemies");
      this->hammersCount = game.at("hammer_count");
      this->levels = game.at("levels");
      this->clientMax = game.at("client_max");
      for(auto& td: game.at("users")) {
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

int Configuration::getHammersCount(){
  return this->hammersCount;
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
  for(int i = 0; i < this->users.size(); i++){
    if(users[i].username == *inputUser && users[i].password == *inputPass){
      found = true;
    }
  }
  return found;
}

char **Configuration::getUsers() {
  char** users = (char**)malloc(this->users.size()*sizeof(char*));
  for (int i = 0; i < this->users.size(); i++) {
    users[i] = (char*)malloc(20*sizeof(char));//20 es la cantidad maxima de caracteres por usuario
  }
  for(int i = 0; i < this->users.size(); i++){
    const char* aux = this->users[i].username.c_str();
    strcpy(users[i],aux);
  }
  return users;
}

int Configuration::getClientMax() {
  return this->clientMax;
}
