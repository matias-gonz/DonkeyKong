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

private:


    Platform** platforms;
    int platformCount;
    SDL_Texture* platformTexture;

    Ladder** stairs;
    int stairCount;
    SDL_Texture* stairTexture;

    Fire** fires;
    int fireCount;
    SDL_Texture* fireTexture;

    void loadPlatforms();

    void loadStairs();

    void loadMovPlatforms();

    void loadFire();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
