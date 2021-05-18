#include "TextureManager.h"
#include "../model/Game.h"
#include "stdio.h"
TextureManager::TextureManager(SDL_Renderer* aRenderer){

    this->renderer = aRenderer;
    this->loadPlatformTexture();
    this->loadLadderTexture();
    this->loadFireTexture();
    this->loadPlayerTexture();
    this->loadEnemyTexture();
    this->loadBossTexture();
}

TextureManager::~TextureManager() {
    delete this->playerTexture;
    delete this->platformTexture;
    delete this->ladderTexture;
    delete this->fireTexture;
    delete this->enemyTexture;
    delete this->bossTexture;
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

void TextureManager::loadPlayerTexture(){
    SDL_Texture* textura =NULL;
    textura = this->loadTexture("resources/sprites/sans_walk.png");
    if(textura == NULL) printf("No se cargo la textura del personaje");
    this->playerTexture = textura;
}

void TextureManager::loadPlatformTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/blueplat.png");
    if(texture == NULL) printf("No se cargo la textura de la plataforma");
    this->platformTexture =  texture;
}

void TextureManager::loadLadderTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/yelstair.png");
    if(texture == NULL) printf("No se cargo la textura de la escalera");
    this->ladderTexture = texture;
}

void TextureManager::loadFireTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/fire.png");
    if(texture == NULL) printf("No se cargo la textura del fuego");
    this->fireTexture =  texture;
}

void TextureManager::loadEnemyTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/fire_walk.png");
    if(texture == NULL) printf("No se cargo la textura del enemigo fuego");
    this->enemyTexture =  texture;
}


void TextureManager::loadBossTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/boss.png");
    if(texture == NULL) printf("No se cargo la textura del Jefe");
    this->bossTexture =  texture;
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

SDL_Texture *TextureManager::getEnemyTexture() {
    return this->enemyTexture;
}

SDL_Texture *TextureManager::getBossTexture(){
    return this->bossTexture;
}
