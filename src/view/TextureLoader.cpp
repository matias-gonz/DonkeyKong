#include "TextureLoader.h"
#include "../model/Game.h"

SDL_Texture* TextureLoader::loadTexture(const char *file) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}