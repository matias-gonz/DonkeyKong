#include "Fire.h"
#include "../view/TextureManager.h"

Fire::Fire(Position position, int count) {
    this->srcRect = new SDL_Rect();
    this->srcRect->x = 0;
    this->srcRect->y = 0;
    this->srcRect->w = 13;
    this->srcRect->h = 15;

    this->destRect = new SDL_Rect();

    this->destRect->x = position.getX();
    this->destRect->y = position.getY();
    this->destRect->w = WIDTH / 32;
    this->destRect->h = this->destRect->w;


    this->count = count;
}

Fire::~Fire() {
    delete this->srcRect;
    delete this->destRect;
}

void Fire::update() {
    this->srcRect->x = this->srcRect->w * (rand() % 4);
}

SDL_Rect *Fire::getDestRect() {
    return destRect;
}

SDL_Rect *Fire::getSrcRect() {
    return srcRect;
}

int Fire::getCount() {
    return this->count;
}

SDL_Rect Fire::getRectangle() {
  SDL_Rect rectangle = *destRect;
  rectangle.w *= 2;
  rectangle.h -= 15;
  rectangle.y += 15;
  return rectangle;
}
