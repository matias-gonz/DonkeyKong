#include "LevelDrawer.h"

LevelDrawer::LevelDrawer(SDL_Renderer *aRenderer, TextureManager *aTextureManager) {
    this->textureManager = aTextureManager;
    this->renderer = aRenderer;
    this->levelnum = 0;
}


void LevelDrawer::draw(Level *level) {
  /*
  this->levelnum = level->getCurrentLevel();
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
  */
}

void LevelDrawer::drawLadder(LadderContainer ladder) {
    SDL_Rect *srcRect = NULL;
    SDL_Rect *destRect = &ladder.dest;
    SDL_Rect *tmpRect = new SDL_Rect();
    tmpRect->x = destRect->x;
    tmpRect->y = destRect->y;
    tmpRect->h = destRect->h;
    tmpRect->w = destRect->w;


    SDL_Texture *ladderTexture = this->textureManager->getLadderTexture(this->levelnum);
    if(!ladderTexture){
        ladderTexture = this->textureManager->getErrorTexture();
        srcRect = NULL;
    }

    for (int i = 0; i < ladder.count; i++) {
        SDL_RenderCopy(this->renderer, ladderTexture, srcRect, tmpRect);
        tmpRect->y -= destRect->h;
    }
}

void LevelDrawer::drawPlatform(PlatformContainer platform) {
    SDL_Rect *srcRect = NULL;
    SDL_Rect *destRect = &platform.dest;
    SDL_Rect *tmpRect = new SDL_Rect();
    tmpRect->x = destRect->x;
    tmpRect->y = destRect->y;
    tmpRect->h = destRect->h;
    tmpRect->w = destRect->w;

    SDL_Texture *platformTexture = this->textureManager->getPlatformTexture(this->levelnum);
    if(!platformTexture){
        platformTexture = this->textureManager->getErrorTexture();
        srcRect = NULL;
    }

    for (int i = 0; i < platform.count; i++) {
        SDL_RenderCopy(this->renderer, platformTexture, srcRect, tmpRect);
        tmpRect->x += destRect->w;
    }
}

void LevelDrawer::drawFire(FireContainer fire) {
    SDL_Rect *srcRect = &fire.src;
    SDL_Rect *destRect = &fire.dest;
    SDL_Rect *tmpRect = new SDL_Rect();
    tmpRect->x = destRect->x;
    tmpRect->y = destRect->y;
    tmpRect->h = destRect->h;
    tmpRect->w = destRect->w;

    SDL_Texture *fireTexture = this->textureManager->getFireTexture();
    if(!fireTexture){
        fireTexture = this->textureManager->getErrorTexture();
        srcRect = NULL;
    }

    for (int i = 0; i < fire.count; i++) {
        SDL_RenderCopy(this->renderer, fireTexture, srcRect, tmpRect);
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

void LevelDrawer::drawPlatforms(PlatformContainer *platforms, int count) {
  for(int i = 0; i < count; i++){
    this->drawPlatform(platforms[i]);
  }
}

void LevelDrawer::drawLadders(LadderContainer *ladders, int ladderCount) {
  for(int i = 0; i < ladderCount; i++){
    this->drawLadder(ladders[i]);
  }
}

void LevelDrawer::drawFires(FireContainer *fires, int fireCount) {
  for(int i = 0; i < fireCount; i++){
    this->drawFire(fires[i]);
  }
}



