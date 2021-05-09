#include "barrel.h"


Barrel::Barrel()
{
    //Initialize the offsets
    posX = 200;
    posY = 0;

    //Initialize the velocity
    velX = 1;
    velY = 1;
}
Barrel::Barrel(LTexture bTexture)
{
    //Initialize the offsets
    posX = 200;
    posY = 0;

    //Initialize the velocity
    velX = 1;
    velY = 1;
    this->barrelTexture=bTexture;
}

void Barrel::move()
{
    //Move the dot down
    posY += velY;
}

void Barrel::render()
{
    //Show the dot
    barrelTexture.render(posX, posY );
}

void Barrel:: setTexture(LTexture* bTexture){
    this->barrelTexture = *bTexture;
}