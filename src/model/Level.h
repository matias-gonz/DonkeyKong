#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVEL_H

#include "SDL2/SDL_image.h"
#include "Platform.h"
#include "Ladder.h"
#include "../view/TextureManager.h"
#include "Fire.h"
#include "barrel.h"
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

    int getBarrelCount();
    Barrel *getBarrel(int i);

private:


    Platform** platforms;
    int platformCount;

    Ladder** ladders;
    int ladderCount;

    Fire** fires;
    int fireCount;

    Barrel** barrels;
    int barrelCount;

    LevelLoader* loader;

    void reset();

    void freePlatforms();

    void freeLadders();

    void freeFires();

    void freeBarrels();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
