#ifndef TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H
#define TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H

#include <fstream>
#include <iostream>

#include "../../resources/libraries/json.hpp"
#include "../view/TextureManager.h"

using json = nlohmann::json;

class Configuration {
public:
  Configuration();

  json getSprites();

  json getLevels();

  int getEnemiesCount();

  json getLogLevel();

  bool isDefault();

private:
  json configuration_json;
  json sprites;
  json log;
  json game;
  json levels;
  int enemiesCount;
  bool loadsDefault = false;

  void setGameConfig();

  void setLogConfig();

  bool hasKey(json json, std::string key);

  void loadDefaultConfig();

};

#endif //TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H
