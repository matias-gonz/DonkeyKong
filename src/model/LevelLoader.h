#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H

#include <fstream>

#include "Platform.h"
#include "Ladder.h"
#include "Barrel.h"
#include "Fire.h"
#include "Hammer.h"

#include "../../resources/libraries/json.hpp"
#include "../controller/Configuration.h"

using json = nlohmann::json;

class LevelLoader {
public:
  LevelLoader();

  ~LevelLoader();

  void loadLevel(int level, Platform ***platforms, Ladder ***ladders, Fire ***fires, int *platformCount,
                 int *ladderCount, int *fireCount, Position ***spawns,
                 int *spawnCount, Configuration *configuration);

  Platform **loadPlatforms(json jsonLevel, int *platformCount);

  Ladder **loadLadders(json jsonLevel, int *ladderCount);

  Fire **loadFire(json jsonLevel, int *fireCount);


  //void writeJSON();
  Position **loadSpawns(json json, int *spawnCount);

private:

  std::string loadLevelFromJson(char const *levelPath, json levels);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H
