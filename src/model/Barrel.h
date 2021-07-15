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
    //The dimensions of the barrel
    //static const int BARREL_WIDTH = 20;
    //static const int BARREL_HEIGHT = 20;

    //Maximum axis velocity of the barrel
    //static const int BARREL_VEL = 10;

    //Initializes the variables
    Barrel();

    //Initializes the variables
    //Barrel(LTexture bTexture);

    //Moves the barrel
    //void move();

    //Shows the barrel on the screen
    //void render();

    //void setTexture(LTexture* bTexture);


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
