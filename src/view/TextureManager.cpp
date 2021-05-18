#include "TextureManager.h"
#include "../model/Game.h"
#include "stdio.h"
TextureManager::TextureManager(SDL_Renderer* aRenderer){
    Logger::log(Logger::Info,"Se inicial la carga de texturas.");
    this->renderer = aRenderer;
    this->loadPlatformTexture();
    this->loadLadderTexture();
    this->loadFireTexture();
    this->loadPlayerTexture();
    this->loadEnemyTexture();
    Logger::log(Logger::Info,"Se finaliza la carga de de texturas.");
}

TextureManager::~TextureManager() {
    delete this->playerTexture;
    delete this->platformTexture;
    delete this->ladderTexture;
    delete this->fireTexture;
    delete this->enemyTexture;
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
    Logger::log(Logger::Info,"Se inicia la carga de textura de Player.");
    SDL_Texture* textura = NULL;
    textura = this->loadTexture("resources/sprites/sans_walk.png");
    if(!textura) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/sans_walk.png\". TextureManager::loadPlayerTexture");
    }
    this->playerTexture = textura;
}

void TextureManager::loadPlatformTexture(){
    Logger::log(Logger::Info,"Se inicia la carga de textura de Platform.");
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/blueplat.png");
    if(!texture) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/blueplat.png\". TextureManager::loadPlatformTexture");
    }
    this->platformTexture =  texture;
}

void TextureManager::loadLadderTexture(){
    Logger::log(Logger::Info,"Se inicia la carga de textura de Ladder.");
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/yelstair.png");
    if(!texture) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/yelstair.png\". TextureManager::loadLadderTexture");
    }
    this->ladderTexture = texture;
}

void TextureManager::loadFireTexture(){
    Logger::log(Logger::Info,"Se inicia la carga de textura de Fire.");
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/fire.png");
    if(!texture) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/fire.png\". TextureManager::loadFireTexture");
    }
    this->fireTexture =  texture;
}

void TextureManager::loadEnemyTexture(){
    Logger::log(Logger::Info,"Se inicia la carga de textura de EnemyFire.");
    SDL_Texture* texture =NULL;
    texture = this->loadTexture("resources/sprites/fire_walk.png");
    if(!texture) {
        Logger::log(Logger::Error,"Error al abrir archivo \"resources/sprites/fire_walk.png\". TextureManager::loadEnemyTexture");
    }
    this->enemyTexture =  texture;
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

