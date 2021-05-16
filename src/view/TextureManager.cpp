#include <iostream>
#include "TextureManager.h"
#include "../model/Game.h"

TextureManager::TextureManager(SDL_Renderer* aRenderer, json sprites){
    this->renderer = aRenderer;
    this->sprites = sprites;
    this->loadPlatformTexture();
    this->loadLadderTexture();
    this->loadFireTexture();
    this->loadPlayerTexture();
}

TextureManager::~TextureManager() {
    delete this->playerTexture;
    delete this->platformTexture;
    delete this->ladderTexture;
    delete this->fireTexture;
}

SDL_Texture* TextureManager::loadTexture(std::string path) {
    //Remove first and last "\"
    path.replace(0, 1, "");
    path.erase(path.size() - 1);
    //The final texture
    SDL_Texture* newTexture = NULL;
    char char_path[path.size() + 1];
    strcpy(char_path, path.c_str());

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(char_path);
    if( loadedSurface != NULL )
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL SDL_Renderer*Error: %s\n", char_path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );

    }
    else
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", char_path, IMG_GetError());
    }

    return newTexture;
}

void TextureManager::loadPlayerTexture(){
    SDL_Texture* textura =NULL;
    textura = this->loadTexture(to_string((sprites.at("player"))));
    if(textura == NULL) printf("No se cargo la textura del personaje");
    this->playerTexture = textura;
}

void TextureManager::loadPlatformTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture(to_string((sprites.at("blue_platform"))));
    if(texture == NULL) printf("No se cargo la textura de la plataforma");
    this->platformTexture =  texture;
}

void TextureManager::loadLadderTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture(to_string((sprites.at("yellow_stair"))));
    if(texture == NULL) printf("No se cargo la textura de la escalera");
    this->ladderTexture = texture;
}

void TextureManager::loadFireTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture(to_string((sprites.at("fire"))));
    if(texture == NULL) printf("No se cargo la textura del fuego");
    this->fireTexture =  texture;
}

SDL_Texture *TextureManager::getPlatformTexture() {
    return this->platformTexture;
}

SDL_Texture *TextureManager::getLadderTexture() {
    return this->ladderTexture;
}

SDL_Texture *TextureManager::getFireTexture() {
    return this->fireTexture;
}

SDL_Texture *TextureManager::getPlayerTexture() {
    return this->playerTexture;
}
