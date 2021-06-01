#include "Ladder.h"

Ladder::Ladder(Position position, int count) {
    this->srcRect = NULL;
    this->destRect = new SDL_Rect();

    this->destRect->x = position.getX();
    this->destRect->y = position.getY();
    this->destRect->w = WIDTH / 32;
    this->destRect->h = this->destRect->w / 4;


    this->count = count;
}

Ladder::~Ladder() {
    delete this->srcRect;
    delete this->destRect;
}

SDL_Rect *Ladder::getDestRect() {
    return destRect;
}

int Ladder::getCount() {
    return count;
}

SDL_Rect *Ladder::getSrcRect() {
    return srcRect;
}

SDL_Rect Ladder::getRectangle() {
    SDL_Rect rectangle = *this->destRect;
    rectangle.y -= rectangle.h*(this->count-1);
    rectangle.h *=(this->count);
    rectangle.x += rectangle.w/2-4;
    rectangle.w = 8;
    return rectangle;
}
