#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVEL_H

#include "SDL2/SDL_image.h"

class Level {

public:
    Level();
    ~Level();

    void loadLevel();
    void drawLevel();

private:
    SDL_Rect src,dest;
    SDL_Texture* platform;

};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
