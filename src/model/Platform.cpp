#include "Platform.h"
#include "../view/TextureManager.h"


Platform::Platform(Position position, int count, int direction) {
    this->srcRect = NULL;
    this->destRect = new SDL_Rect();

    this->destRect->x = position.getX();
    this->destRect->y = position.getY();
    this->destRect->w = WIDTH/32;
    this->destRect->h = this->destRect->w/1.5;
    this->count = count;
    this->movement = new PlatformMovement(direction);
}

Platform::~Platform() {
    delete this->srcRect;
    delete this->destRect;
    delete this->movement;
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

SDL_Rect *Platform::getSrcRect() {
    return srcRect;
}

SDL_Rect Platform::getRectangle() {
    SDL_Rect rectangle = *this->destRect;
    rectangle.w *=this->count;
    return rectangle;
}

