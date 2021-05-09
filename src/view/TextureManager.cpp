#include "TextureManager.h"
#include "../model/Game.h"

TextureManager::TextureManager(SDL_Renderer* aRenderer){
    this->renderer = aRenderer;
}

SDL_Texture* TextureManager::LoadTexture(const char *file) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}
SDL_Texture* TextureManager::loadTexture(const char* path, SDL_Renderer* aRenderer ) {
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
    SDL_RenderCopy(this->renderer,texture,srcRect,destRect);
}

SDL_Texture* TextureManager::loadPlayerTexture(){
    SDL_Texture* textura =NULL;
    textura = this->LoadTexture("/home/agustin/CLionProjects/Taller-Prog-I-2021-1C-KIWI/resources/sprites/sans_left.png");
    if(textura = NULL) printf("No se cargo la textura del personaje");
    return textura;
}

SDL_Texture* TextureManager::loadPlatformTexture(){
    SDL_Texture* texture =NULL;
    texture = this->LoadTexture("/home/agustin/CLionProjects/Taller-Prog-I-2021-1C-KIWI/resources/sprites/blueplat.png");
    if(texture = NULL) printf("No se cargo la textura de la plataforma");
    return texture;
}

SDL_Texture* TextureManager::loadLadderTexture(){
    SDL_Texture* texture =NULL;
    texture = this->LoadTexture("/home/agustin/CLionProjects/Taller-Prog-I-2021-1C-KIWI/resources/sprites/yelstair.png");
    if(texture = NULL) printf("No se cargo la textura de la escalera");
    return texture;
}