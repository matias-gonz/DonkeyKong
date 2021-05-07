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

void Platform::draw(SDL_Texture *texture) {
    SDL_Rect* tmpRect = new SDL_Rect();
    tmpRect->x = this->destRect->x;
    tmpRect->y = this->destRect->y;
    tmpRect->h = this->destRect->h;
    tmpRect->w = this->destRect->w;

    for(int i = 0; i < this->count; i++){
        TextureManager::DrawTexture(texture,this->srcRect,tmpRect);
        tmpRect->x += this->destRect->w;
    }

}

