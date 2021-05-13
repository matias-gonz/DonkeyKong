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

    void writeJSON();

    Platform **loadPlatforms(char *levelDir, int *platformCount);

    Ladder **loadLadders(char *levelDir, int *ladderCount);

    Fire **loadFire(char *levelDir, int *fireCount);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVELLOADER_H
