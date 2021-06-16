#ifndef TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H
#define TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H

#include <fstream>
#include <iostream>

#include "../../resources/libraries/json.hpp"
#include "../view/TextureManager.h"
#include "../Constants.h"

using json = nlohmann::json;

class Configuration {
public:
  Configuration();

  json getSprites();

  json getLevels();

  int getEnemiesCount();

  json getLogLevel();

  bool isDefault();

  bool checkCredentials(std::string *inputUser, std::string *inputPass);

    char **getUsers();

    int getClientMax();

private:
  json configuration_json;
  json sprites;
  json log;
  json game;
  json levels;
  int enemiesCount;
  bool loadsDefault = false;
  int clientMax;
  struct User {
    std::string username;
    std::string password;
  };
  User user;
  std::vector<User> users;

  void setGameConfig();

  void setLogConfig();

  bool hasKey(json json, std::string key);

  void loadDefaultConfig();


};

#endif //TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H
