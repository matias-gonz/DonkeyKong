#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVEL_H

#include "SDL2/SDL_image.h"
#include "Platform.h"
#include "Ladder.h"
#include "../view/TextureManager.h"
#include "Fire.h"

class Level {

public:
    Level();
    ~Level();

    void loadLevel();
    void drawLevel();
    void update();

    int getLadderCount();
    Ladder *getLadder(int i);

    int getPlatformCount();
    Platform *getPlatform(int i);

    int getFireCount();
    Fire *getFire(int i);

private:


    Platform** platforms;
    int platformCount;

    Ladder** stairs;
    int stairCount;

    Fire** fires;
    int fireCount;

    void loadPlatforms();

    void loadStairs();

    void loadMovPlatforms();

    void loadFire();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
