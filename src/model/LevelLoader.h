#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H

#include <fstream>

#include "../../resources/libraries/json.hpp"
#include "Platform.h"
#include "Ladder.h"
#include "Barrel.h"
#include "Fire.h"

using json = nlohmann::json;

class LevelLoader {
public:

    LevelLoader();
    ~LevelLoader();

    void
    loadLevel(int level, Platform ***platforms, Ladder ***ladders, Fire ***fires, Barrel ***barrels, int *platformCount, int *ladderCount,
              int *fireCount, int *barrelCount, Position ***spawns, int *spawnCount);

    Platform **loadPlatforms(json jsonLevel, int *platformCount);

    Ladder **loadLadders(json jsonLevel, int *ladderCount);

    Fire **loadFire(json jsonLevel, int *fireCount);

    Barrel **loadBarrel(json jsonLevel, int *levelCount);

    //void writeJSON();
    Position **loadSpawns(json json, int *spawnCount);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H
