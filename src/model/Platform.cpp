#include "Platform.h"
#include "../view/TextureManager.h"


Platform::Platform(Position position, int count) {
    this->srcRect = NULL;
    this->destRect = new SDL_Rect();

    this->destRect->x = position.getX();
    this->destRect->y = position.getY();
    this->destRect->w = WIDTH/32;
    this->destRect->h = this->destRect->w/1.5;
    this->count = count;
}

SDL_Rect *Platform::getDestRect() {
    return destRect;
}

int Platform::getCount() {
    return count;
}

const SDL_Rect *Platform::getSrcRect() {
    return srcRect;
}
