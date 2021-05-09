#include "LevelDrawer.h"

LevelDrawer::LevelDrawer(SDL_Renderer *aRenderer, TextureManager *aTextureManager) {
    this->textureManager = aTextureManager;
    this->renderer = aRenderer;
}


void LevelDrawer::draw(Level* level) {
    for(int i = 0; i < level->getStairCount(); i++){
        Ladder* aLadder =level->getLedder(i);
        this->drawLadder(aLadder);
    }
    for (int i = 0; i < level->getPlatformCount(); i++) {
        Platform* aPlatform = level->getPlatform(i);
        this->drawPlatform(aPlatform);
    }

}

void LevelDrawer::drawLadder(Ladder* ladder) {

    SDL_Rect* destRect = ladder->getDestRect();
    SDL_Rect* tmpRect = new SDL_Rect();
    tmpRect->x = destRect->x;
    tmpRect->y = destRect->y;
    tmpRect->h = destRect->h;
    tmpRect->w = destRect->w;

    SDL_Texture* ladderTexture = this->textureManager->loadLadderTexture();

    for(int i = 0; i < ladder->getCount(); i++){
        SDL_RenderCopy(this->renderer,ladderTexture,ladder->getSrcRect(),tmpRect);
        tmpRect->y -= destRect->h;
    }
}

void LevelDrawer::drawPlatform(Platform *platform) {

    SDL_Rect* destRect = platform->getDestRect();
    SDL_Rect* tmpRect = new SDL_Rect();
    tmpRect->x = destRect->x;
    tmpRect->y = destRect->y;
    tmpRect->h = destRect->h;
    tmpRect->w = destRect->w;

    SDL_Texture* ladderTexture = this->textureManager->loadLadderTexture();

    for(int i = 0; i < platform->getCount(); i++){
        SDL_RenderCopy(this->renderer,ladderTexture,platform->getSrcRect(),tmpRect);
        tmpRect->y -= destRect->h;
    }
}

