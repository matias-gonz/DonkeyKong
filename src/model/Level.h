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

    void loadLevel(int levelnum);
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

    Ladder** ladders;
    int ladderCount;

    Fire** fires;
    int fireCount;

    void loadPlatforms(int i);

    void loadStairs(int i);

    void loadMovPlatforms(int i);

    void loadFire(int i);

    void reset();

    void freePlaforms();

    void freeLadders();

    void freeFires();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
