#include "Barrel.h"


Barrel::Barrel()
{
    //Initialize the offsets
    //posX = 200;
    //posY = 0;

    //Initialize the velocity
    //velX = 1;
    //velY = 1;
}
Barrel::Barrel(Position position, int count, int direction){
    this->srcRect = NULL;
    this->destRect = new SDL_Rect();

    this->destRect->x = position.getX();
    this->destRect->y = position.getY();
    this->destRect->w = WIDTH/7;
    this->destRect->h = this->destRect->w/1.5;
    this->count = count;
    this->movement = new BarrelMovement(direction);
}
Barrel::~Barrel() {
    delete this->srcRect;
    delete this->destRect;
    delete this->movement;
}

void Barrel::update() {
    if(movement){
        movement->update(this->destRect);
    }
}

SDL_Rect *Barrel::getDestRect() {
    return destRect;
}

SDL_Rect *Barrel::getSrcRect() {
    return srcRect;
}

int Barrel::getCount() {
    return count;
}




/*
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

*/