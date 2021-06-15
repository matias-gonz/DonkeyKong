#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYERINDICATOR_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYERINDICATOR_H

#include <SDL_rect.h>
#include "ltexture.h"

class PlayerIndicator {
private:
    int user;
    SDL_Rect rect;
public:
    void show(SDL_Rect* rect, LTexture* box);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYERINDICATOR_H
