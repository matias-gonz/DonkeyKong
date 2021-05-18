#include "LevelDrawer.h"

LevelDrawer::LevelDrawer(SDL_Renderer *aRenderer, TextureManager *aTextureManager) {
    this->textureManager = aTextureManager;
    this->renderer = aRenderer;
}


void LevelDrawer::draw(Level *level) {
    for (int i = 0; i < level->getLadderCount(); i++) {
        Ladder *aLadder = level->getLadder(i);
        this->drawLadder(aLadder);
    }
    for (int i = 0; i < level->getPlatformCount(); i++) {
        Platform *aPlatform = level->getPlatform(i);
        this->drawPlatform(aPlatform);
    }
    for (int i = 0; i < level->getFireCount(); i++) {
        Fire *aFire = level->getFire(i);
        this->drawFire(aFire);
    }
    for (int i=0; i < level-> getBarrelCount(); i++){
        Barrel *aBarrel = level->getBarrel(i);
        this->drawBarrel(aBarrel);
    }

}

void LevelDrawer::drawLadder(Ladder *ladder) {

    SDL_Rect *destRect = ladder->getDestRect();
    SDL_Rect *tmpRect = new SDL_Rect();
    tmpRect->x = destRect->x;
    tmpRect->y = destRect->y;
    tmpRect->h = destRect->h;
    tmpRect->w = destRect->w;

    SDL_Texture *ladderTexture = this->textureManager->getLadderTexture();

    for (int i = 0; i < ladder->getCount(); i++) {
        SDL_RenderCopy(this->renderer, ladderTexture, ladder->getSrcRect(), tmpRect);
        tmpRect->y -= destRect->h;
    }
}

void LevelDrawer::drawPlatform(Platform *platform) {

    SDL_Rect *destRect = platform->getDestRect();
    SDL_Rect *tmpRect = new SDL_Rect();
    tmpRect->x = destRect->x;
    tmpRect->y = destRect->y;
    tmpRect->h = destRect->h;
    tmpRect->w = destRect->w;

    SDL_Texture *platformTexture = this->textureManager->getPlatformTexture();

    for (int i = 0; i < platform->getCount(); i++) {
        SDL_RenderCopy(this->renderer, platformTexture, platform->getSrcRect(), tmpRect);
        tmpRect->x += destRect->w;
    }
}

void LevelDrawer::drawFire(Fire *fire) {
    SDL_Rect *destRect = fire->getDestRect();
    SDL_Rect *tmpRect = new SDL_Rect();
    tmpRect->x = destRect->x;
    tmpRect->y = destRect->y;
    tmpRect->h = destRect->h;
    tmpRect->w = destRect->w;

    SDL_Texture *fireTexture = this->textureManager->getFireTexture();

    for (int i = 0; i < fire->getCount(); i++) {
        SDL_RenderCopy(this->renderer, fireTexture, fire->getSrcRect(), tmpRect);
        tmpRect->x += destRect->w;
    }
}

void LevelDrawer::drawBarrel(Barrel *barrel) {
    SDL_Rect *destRect = barrel->getDestRect();
    SDL_Rect *tmpRect = new SDL_Rect();
    tmpRect->x = destRect->x;
    tmpRect->y = destRect->y;
    tmpRect->h = destRect->h;
    tmpRect->w = destRect->w;

    SDL_Texture *barrelTexture = this->textureManager->getBarrelTexture();

    SDL_RenderCopy(this->renderer, barrelTexture, NULL, tmpRect);

}


