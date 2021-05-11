#ifndef TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H
#define TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H

#include <fstream>

#include "../../resources/libraries/json.hpp"

using json = nlohmann::json;

class Configuration {
public:
  Configuration();

private:
  json configuration_json;
  json game;
  json log;

  void setGameConfig(json& game_json);

  void setLogConfig(json& log_json);

};

#endif //TALLER_PROG_I_2021_1C_KIWI_CONFIGURATION_H
