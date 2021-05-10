#include "Platform.h"
#include "../view/TextureManager.h"


Platform::Platform(Position position, int count, bool moving) {
    this->srcRect = NULL;
    this->destRect = new SDL_Rect();

    this->destRect->x = position.getX();
    this->destRect->y = position.getY();
    this->destRect->w = WIDTH/32;
    this->destRect->h = this->destRect->w/1.5;
    this->count = count;
    this->movement = new PlatformMovement(moving);
}

SDL_Rect *Platform::getDestRect() {
    return destRect;
}

int Platform::getCount() {
    return count;
}


void Platform::update() {
    if(movement){
        movement->update(this->destRect);
    }

}

const SDL_Rect *Platform::getSrcRect() {
    return srcRect;
}

