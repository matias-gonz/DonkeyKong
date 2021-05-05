#include "TextureManager.h"
#include "../model/Game.h"

SDL_Texture* TextureManager::LoadTexture(const char *file) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}

void TextureManager::DrawTexture(SDL_Texture *texture, SDL_Rect* srcRect, SDL_Rect* destRect) {
    SDL_RenderCopy(Game::renderer,texture,srcRect,destRect);
}