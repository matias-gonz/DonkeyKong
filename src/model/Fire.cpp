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
    this->destRect->w = WIDTH/32;
    this->destRect->h = this->destRect->w;


    this->count = count;
}

void Fire::draw(SDL_Texture *texture) {
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

void Fire::update() {
    this->srcRect->x = this->srcRect->w*(rand()%4);
}
