#ifndef TALLER_PROG_I_2021_1C_KIWI_LADDER_H
#define TALLER_PROG_I_2021_1C_KIWI_LADDER_H

#include "SDL2/SDL_image.h"
#include "Position.h"
#include "../view/TextureManager.h"
#include "../Constants.h"

class Ladder {
public:
    Ladder(Position position, int count);

    ~Ladder();

    SDL_Rect *getDestRect();

    int getCount();

    SDL_Rect *getSrcRect();

    SDL_Rect getRectangle();

private:
    int count;
    SDL_Rect *srcRect;
    SDL_Rect *destRect;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_LADDER_H
