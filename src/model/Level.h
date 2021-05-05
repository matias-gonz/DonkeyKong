#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVEL_H

#include "SDL2/SDL_image.h"
#include "Platform.h"

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

};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
