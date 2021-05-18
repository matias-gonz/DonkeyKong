#include <iostream>
#include "TextureManager.h"
#include "../model/Game.h"
#include "stdio.h"

TextureManager::TextureManager(SDL_Renderer* aRenderer){
    Logger::log(Logger::Info,"Se inicial la carga de texturas.");

TextureManager::TextureManager(SDL_Renderer* aRenderer, json sprites){
    this->renderer = aRenderer;
    this->sprites = sprites;
    this->loadPlatformTexture();
    this->loadLadderTexture();
    this->loadFireTexture();
    this->loadPlayerTexture();
    this->loadBarrelTexture();
    this->loadEnemyTexture();
    this->loadErrorTexture();
    Logger::log(Logger::Info,"Se finaliza la carga de de texturas.");
    this->loadBossTexture();
    this->loadPrincessTexture();
}

TextureManager::~TextureManager() {
    delete this->playerTexture;
    delete this->bluePlatformTexture;
    delete this->redPlatformTexture;
    delete this->yellowLadderTexture;
    delete this->cyanLadderTexture;
    delete this->fireTexture;
    delete this->barrelTexture;
    delete this->enemyTexture;
    delete this->bossTexture;
    delete this->princessTexture;
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
    Logger::log(Logger::Info,"Se inicia la carga de textura de Player.");
    if(!textura) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/sans_walk.png\". TextureManager::loadPlayerTexture");
    }
    this->playerTexture = textura;
}

void TextureManager::loadPlatformTexture(){
    Logger::log(Logger::Info,"Se inicia la carga de textura de Platform.");
    SDL_Texture* texture =NULL;
    texture = this->loadTexture(to_string((sprites.at("blue_platform"))));
    if(!texture) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/blueplat.png\". TextureManager::loadPlatformTexture");
    }
    this->bluePlatformTexture =  texture;
}

void TextureManager::loadLadderTexture(){
    Logger::log(Logger::Info,"Se inicia la carga de textura de Ladder.");
    SDL_Texture* texture =NULL;
    texture = this->loadTexture(to_string((sprites.at("yellow_stair"))));
    if(texture == NULL) printf("No se cargo la textura de la escalera");
    if(!texture) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/cyanladder.png\". TextureManager::loadLadderTexture");
    }
    this->cyanLadderTexture = texture;

}

void TextureManager::loadFireTexture(){
    Logger::log(Logger::Info,"Se inicia la carga de textura de Fire.");
    SDL_Texture* texture =NULL;
    texture = this->loadTexture(to_string((sprites.at("fire"))));
    if(!texture) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/fire.png\". TextureManager::loadFireTexture");
    }
    this->fireTexture =  texture;
}

void TextureManager::loadBarrelTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/barrel_right.png");
    if(texture == NULL) printf("No se cargo la textura del barril");
    this->barrelTexture =  texture;
}
/*
SDL_Texture *TextureManager::getPlatformTexture() {
    return this->platformTexture;
}
*/
void TextureManager::loadEnemyTexture(){
    Logger::log(Logger::Info,"Se inicia la carga de textura de EnemyFire.");
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/fire_walk.png");
    if(!texture) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/fire_walk.png\". TextureManager::loadEnemyTexture");
    }
    this->enemyTexture =  texture;
}

void TextureManager::loadErrorTexture() {
    Logger::log(Logger::Info, "Se inicia la carga de textura de error.");
    SDL_Texture *texture = NULL;
    texture = this->loadTexture("resources/sprites/errortexture.png");
    if (!texture) {
        Logger::log(Logger::Error,
                    "Error al abrir archivo \"resources/sprites/errortexture.png\". TextureManager::loadErrorTexture");
    }
    this->errorTexture = texture;

}

void TextureManager::loadBossTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/boss_still.png");
    if(texture == NULL) printf("No se cargo la textura del Jefe");
    this->bossTexture =  texture;
}

void TextureManager::loadPrincessTexture(){
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/princess_still.png");
    if(texture == NULL) printf("No se cargo la textura dela princesa");
    this->princessTexture =  texture;
}

SDL_Texture *TextureManager::getPlatformTexture(int levelnum) {
    if(levelnum == 1){
        return this->bluePlatformTexture;
    }
    return this->redPlatformTexture;
}

SDL_Texture *TextureManager::getLadderTexture(int levelnum) {
    if(levelnum == 1){
        return this->yellowLadderTexture;
    }
    return this->cyanLadderTexture;
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

SDL_Texture *TextureManager::getErrorTexture() {
    return this->errorTexture;
}



SDL_Texture *TextureManager::getBossTexture(){
    return this->bossTexture;
}

SDL_Texture *TextureManager::getPrincessTexture() {
    return this->princessTexture;
}
SDL_Texture *TextureManager::getBarrelTexture() {
    return this->barrelTexture;
}
