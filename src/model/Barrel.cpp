#include "Barrel.h"


Barrel::Barrel()
{
    //Initialize the offsets
    //posX = 200;
    //posY = 0;
}
Barrel::Barrel(Position position, int count, int direction){
    this->srcRect = NULL;
    this->destRect = new SDL_Rect();

    this->destRect->x = 0;//position.getX();
    this->destRect->y = 0;//position.getY();
    this->destRect->w = WIDTH/7;
    this->destRect->h = this->destRect->w/1.5;
    this->count = count;
    this->movement = new BarrelMovement(direction);
    this->pos = &position;
}
Barrel::~Barrel() {
    delete this->srcRect;
    delete this->destRect;
    delete this->movement;
}

void Barrel::update() {
    if(movement){
        movement->update(this->destRect);
        this->pos->setX(this->destRect->x);
        this->pos->setY(this->destRect->y);
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

void Barrel::moveUp(int i) {
  this->destRect->y -= i;
}

void Barrel::resetVelY() {
  this->movement->resetVelY();
}

int Barrel::getDistance() {
  this->movement->getDistance();
}
