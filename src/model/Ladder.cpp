#include "Ladder.h"

Ladder::Ladder(Position position, int count) {
    this->srcRect = NULL;
    this->destRect = NULL;

    this->destRect = new SDL_Rect();

    this->destRect->x = position.getX();
    this->destRect->y = position.getY();
    this->destRect->w = WIDTH/32;
    this->destRect->h = this->destRect->w/4;


    this->count = count;
}

SDL_Rect *Ladder::getDestRect() {
    return destRect;
}

int Ladder::getCount() {
    return count;
}

const SDL_Rect *Ladder::getSrcRect() {
    return srcRect;
}
