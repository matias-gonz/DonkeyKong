#ifndef TALLER_PROG_I_2021_1C_KIWI_BARREL_H
#define TALLER_PROG_I_2021_1C_KIWI_BARREL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/ltexture.h"
#include "Position.h"
#include "BarrelMovement.h"


#define HEIGHT 576
#define WIDTH 1024

//The Barrel that will move around on the screen
class Barrel
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
    Barrel(Position position, int count, int direction);
    ~Barrel();
    SDL_Rect *getDestRect();
    SDL_Rect *getSrcRect();
    void update();
    int getCount();

private:
    //The X and Y offsets of the barrel
    //int posX, posY;

    //The velocity of the barrel
    //int velX, velY;

    //LTexture barrelTexture;


    //CAMBIOS BARREL
    int count;
    BarrelMovement* movement;
    SDL_Rect* srcRect;
    SDL_Rect * destRect;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_BARREL_H
