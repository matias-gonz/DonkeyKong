#ifndef TALLER_PROG_I_2021_1C_KIWI_BARREL_H
#define TALLER_PROG_I_2021_1C_KIWI_BARREL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/ltexture.h"
#include "Position.h"
#include "../Constants.h"
#include "Entity.h"


//The Barrel that will move around on the screen
class Barrel: public Entity
{
public:
    Barrel();
    //CAMBIOS BARREL
    Barrel(Position *position);
    ~Barrel();
    SDL_Rect *getDestRect();
    SDL_Rect *getSrcRect();
    void update();
    int getCount();

    void moveUp(int i);

    void resetVelY();

private:
    int width;
    int height;
    int x;
    int y;

};

#endif //TALLER_PROG_I_2021_1C_KIWI_BARREL_H
