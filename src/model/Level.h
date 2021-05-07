#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVEL_H

#include "SDL2/SDL_image.h"
#include "Platform.h"
#include "Stair.h"
#include "../view/TextureManager.h"

class Level {

public:
    Level();
    ~Level();

    void loadLevel();
    void drawLevel();

private:


    Platform** platforms;
    int platformCount;
    SDL_Texture* platformTexture;

    Stair** stairs;
    int stairCount;
    SDL_Texture* stairTexture;

    void loadPlatforms();

    void loadStairs();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
