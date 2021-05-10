#include "TextureManager.h"
#include "../model/Game.h"

TextureManager::TextureManager(SDL_Renderer* aRenderer){
    this->renderer = aRenderer;
}

SDL_Texture* TextureManager::loadTexture(const char *path) {
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface != NULL )
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface );
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

SDL_Texture* TextureManager::loadPlayerTexture(){
    SDL_Texture* textura =NULL;
    textura = this->loadTexture("resources/sprites/sans_walk.png");
    if(textura == NULL) printf("No se cargo la textura del personaje");
    return textura;
}

SDL_Texture* TextureManager::loadPlatformTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/blueplat.png");
    if(texture == NULL) printf("No se cargo la textura de la plataforma");
    return texture;
}

SDL_Texture* TextureManager::loadLadderTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/yelstair.png");
    if(texture == NULL) printf("No se cargo la textura de la escalera");
    return texture;
}