#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVEL_H

#include "SDL2/SDL_image.h"
#include "Platform.h"
#include "Ladder.h"
#include "../view/TextureManager.h"

class Level {

public:
    Level();
    ~Level();

    void loadLevel();
    void drawLevel();

    int getStairCount();

    Ladder *getLedder(int i);

    int getPlatformCount();

    Platform *getPlatform(int i);

private:


    Platform** platforms;
    int platformCount;

    Ladder** stairs;
    int stairCount;

    void loadPlatforms();

    void loadStairs();

    void loadMovPlatforms();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
