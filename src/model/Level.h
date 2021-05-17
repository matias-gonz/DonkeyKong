#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVEL_H

#include "SDL2/SDL_image.h"
#include "Platform.h"
#include "Ladder.h"
#include "../view/TextureManager.h"
#include "Fire.h"
#include "LevelLoader.h"

class Level {

public:
    Level();

    ~Level();

    void loadLevel(int levelnum);

    void update();

    int getLadderCount();

    Ladder *getLadder(int i);

    int getPlatformCount();

    Platform *getPlatform(int i);

    int getFireCount();

    Fire *getFire(int i);

private:

    Platform **platforms;
    int platformCount;

    Ladder **ladders;
    int ladderCount;

    Fire **fires;
    int fireCount;

    Position **spawns;
    int spawnCount;

    LevelLoader *loader;



    void reset();

    void freePlaforms();

    void freeLadders();

    void freeFires();

    void freeSpawns();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
