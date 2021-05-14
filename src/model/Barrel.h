#ifndef TALLER_PROG_I_2021_1C_KIWI_BARREL_H
#define TALLER_PROG_I_2021_1C_KIWI_BARREL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/ltexture.h"

//The dot that will move around on the screen
class Barrel {
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int DOT_VEL = 10;

    //Initializes the variables
    Barrel();

    //Initializes the variables
    Barrel(LTexture bTexture);

    //Moves the dot
    void move();

    //Shows the dot on the screen
    void render();

    void setTexture(LTexture *bTexture);

private:
    //The X and Y offsets of the dot
    int posX, posY;

    //The velocity of the dot
    int velX, velY;

    LTexture barrelTexture;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_BARREL_H
