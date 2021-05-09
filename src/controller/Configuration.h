#ifndef TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H
#define TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H

#include <fstream>

#include "../../resources/libraries/json.hpp"
#include "../model/Enemy.h"
#include "../view/viewManager.h"

using json = nlohmann::json;

class Configuration {
public:
  Configuration();
  json log;

private:
  json configuration_json;
  json game;
  Enemy* enemy;
  ViewManager* viewManager;

  void setGameConfig(json& game_json);

  void setLogConfig(json& log_json);

};

#endif //TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H
