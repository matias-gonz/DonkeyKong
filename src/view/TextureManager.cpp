#include "TextureManager.h"
#include "../model/Game.h"

TextureManager::TextureManager(SDL_Renderer* aRenderer){
    this->renderer = aRenderer;
}

SDL_Texture* TextureManager::LoadTexture(const char *file) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}
SDL_Texture* TextureManager::LoadTexture(const char* path,SDL_Renderer* aRenderer ) {
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface != NULL )
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(aRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL SDL_Renderer*Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );

    }
    else
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }

    return newTexture;
}
void TextureManager::DrawTexture(SDL_Texture *texture, SDL_Rect* srcRect, SDL_Rect* destRect) {
    SDL_RenderCopy(Game::renderer,texture,srcRect,destRect);
}

SDL_Texture* TextureManager::loadPlayerTexture(){
    return TextureManager::LoadTexture("resources/sprites/sans_left.png");
}
