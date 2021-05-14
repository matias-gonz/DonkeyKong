#ifndef TALLER_PROG_I_2021_1C_KIWI_LADDER_H
#define TALLER_PROG_I_2021_1C_KIWI_LADDER_H

#include "SDL2/SDL_image.h"
#include "Position.h"
#include "../view/TextureManager.h"

#define HEIGHT 576
#define WIDTH 1024

class Ladder {
public:
    Ladder(Position position, int count);

    ~Ladder();

    SDL_Rect *getDestRect();

    int getCount();

    const SDL_Rect *getSrcRect();

private:
    int count;
    SDL_Rect *srcRect;
    SDL_Rect *destRect;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_LADDER_H
