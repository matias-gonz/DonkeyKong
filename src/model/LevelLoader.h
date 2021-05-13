#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H

#include <fstream>

#include "../../resources/libraries/json.hpp"
#include "Platform.h"
#include "Ladder.h"
#include "Fire.h"

using json = nlohmann::json;

class LevelLoader {
public:

    LevelLoader();
    ~LevelLoader();

    void loadLevel(int level, Platform*** platforms, Ladder*** ladders, Fire*** fires, int* platformCount, int* ladderCount, int* fireCount);

    Platform **loadPlatforms(json jsonLevel, int *platformCount);

    Ladder **loadLadders(json jsonLevel, int *ladderCount);

    Fire **loadFire(json jsonLevel, int *fireCount);

    //void writeJSON();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H
