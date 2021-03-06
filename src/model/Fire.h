#ifndef TALLER_PROG_I_2021_1C_KIWI_FIRE_H
#define TALLER_PROG_I_2021_1C_KIWI_FIRE_H

#include "Position.h"
#include "SDL2/SDL_image.h"
#include "../Constants.h"

class Fire {
public:
    Fire(Position position, int count);

    ~Fire();

    SDL_Rect *getDestRect();

    SDL_Rect *getSrcRect();

    void update();

    int getCount();

    SDL_Rect getRectangle();

private:
    Position pos;
    int count;
    SDL_Rect *srcRect;
    SDL_Rect *destRect;

};


#endif //TALLER_PROG_I_2021_1C_KIWI_FIRE_H
