#ifndef TALLER_PROG_I_2021_1C_KIWI_PLATFORM_H
#define TALLER_PROG_I_2021_1C_KIWI_PLATFORM_H
#include "SDL2/SDL_image.h"
#include "Position.h"
#include "PlatformMovement.h"
#include "../Constants.h"


class Platform {
public:

    Platform(Position position, int count, int direction);
    ~Platform();

    SDL_Rect *getDestRect();

    int getCount();

    SDL_Rect *getSrcRect();


    void update();

    SDL_Rect getRectangle();

private:
    int count;
    SDL_Rect* srcRect;
    SDL_Rect* destRect;
    PlatformMovement* movement;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLATFORM_H
