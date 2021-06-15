#include <iostream>
#include "TextureManager.h"
#include "../model/Game.h"
#include "stdio.h"

TextureManager::TextureManager(SDL_Renderer *aRenderer, json sprites) {
  this->renderer = aRenderer;
  this->sprites = sprites;
  this->loadPlatformTexture();
  this->loadLadderTexture();
  this->loadFireTexture();
  this->loadPlayersTextures();
  this->loadInactivePlayerTexture();
  this->loadBarrelTexture();
  this->loadEnemyTexture();
  this->loadErrorTexture();
  this->loadBossTexture();
  this->loadPrincessTexture();
  Logger::log(Logger::Info, "Se finaliza la carga de texturas.");
}

TextureManager::~TextureManager() {
  for(int i = 0; i < 5;i++) {
    delete this->playersTextures[i];
  }
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

SDL_Texture *TextureManager::loadTexture(std::string path) {
  //Remove first and last "\"
  path.replace(0, 1, "");
  path.erase(path.size() - 1);
  //The final texture
  SDL_Texture *newTexture = NULL;
  char char_path[path.size() + 1];
  strcpy(char_path, path.c_str());

  //Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(char_path);
  if (loadedSurface != NULL) {
    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL SDL_Renderer*Error: %s\n", char_path, SDL_GetError());
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

  } else {
    printf("Unable to load image %s! SDL_image Error: %s\n", char_path, IMG_GetError());
  }

  return newTexture;
}

void TextureManager::loadPlayersTextures() {
  for(int i = 0; i < 5;i++) {
    SDL_Texture *textura = NULL;
    char path[10];
    strcpy(path,"player_");
    char i_s = i+1 + '0';
    strcat(path, &i_s);
    textura = this->loadTexture(this->loadTextureFromJson(path));
    Logger::log(Logger::Info, "Se inicia la carga de textura de Player.");
    if (!textura) {
      Logger::log(Logger::Error,
                  "Error al abrir archivo \"resources/sprites/sans_walk.png\". TextureManager::loadPlayerTexture\n"
                  "Se cargó una imagen por defecto para el jugador.");
    }
    this->playersTextures[i] = textura;
  }
}

void TextureManager::loadPlatformTexture() {
  Logger::log(Logger::Info, "Se inicia la carga de textura de Platform.");
  SDL_Texture *texture = NULL;
  texture = this->loadTexture(this->loadTextureFromJson("blue_platform"));
  if (!texture) {
    Logger::log(Logger::Error,
                "Error al abrir archivo \"resources/sprites/blueplat.png\". TextureManager::loadPlatformTexture");
  }
  this->bluePlatformTexture = texture;

  texture = this->loadTexture(this->loadTextureFromJson("red_platform"));
  if (!texture) {
    Logger::log(Logger::Error,
                "Error al abrir archivo \"resources/sprites/redplat.png\". TextureManager::loadPlatformTexture");
  }
  this->redPlatformTexture = texture;
}

void TextureManager::loadLadderTexture() {
  Logger::log(Logger::Info, "Se inicia la carga de textura de Ladder.");
  SDL_Texture *texture = NULL;
  texture = this->loadTexture(this->loadTextureFromJson("yellow_stair"));
  if (!texture) {
    Logger::log(Logger::Error,
                "Error al abrir archivo \"resources/sprites/yellow_stair.png\". TextureManager::loadLadderTexture");
  }
  this->yellowLadderTexture = texture;

  texture = this->loadTexture(this->loadTextureFromJson("cyan_ladder"));
  if (!texture) {
    Logger::log(Logger::Error,
                "Error al abrir archivo \"resources/sprites/cyan_ladder.png\". TextureManager::loadLadderTexture");
  }
  this->cyanLadderTexture = texture;
}

void TextureManager::loadFireTexture() {
  Logger::log(Logger::Info, "Se inicia la carga de textura de Fire.");
  SDL_Texture *texture = NULL;
  texture = this->loadTexture(this->loadTextureFromJson("fire"));
  if (!texture) {
    Logger::log(Logger::Error,
                "Error al abrir archivo \"resources/sprites/fire.png\". TextureManager::loadFireTexture");
  }
  this->fireTexture = texture;
}

void TextureManager::loadBarrelTexture() {
  SDL_Texture *texture = NULL;
  texture = this->loadTexture(this->loadTextureFromJson("barrel_right"));
  if (!texture) {
    Logger::log(Logger::Error,
                "Error al abrir archivo \"resources/sprites/barrel_right.png\". TextureManager::loadBarrelTexture");
  }
  this->barrelTexture = texture;
}

void TextureManager::loadEnemyTexture() {
  Logger::log(Logger::Info, "Se inicia la carga de textura de EnemyFire.");
  SDL_Texture *texture = NULL;
  texture = this->loadTexture(this->loadTextureFromJson("enemy"));
  if (!texture) {
    Logger::log(Logger::Error,
                "Error al abrir archivo \"resources/sprites/fire_walk.png\". TextureManager::loadEnemyTexture");
  }
  this->enemyTexture = texture;
}

void TextureManager::loadBossTexture() {
  SDL_Texture *texture = NULL;
  texture = this->loadTexture(this->loadTextureFromJson("boss"));
  if (texture == NULL) printf("No se cargo la textura del Jefe");
  this->bossTexture = texture;
}

void TextureManager::loadPrincessTexture() {
  SDL_Texture *texture = NULL;
  texture = this->loadTexture(this->loadTextureFromJson("princess"));
  if (texture == NULL) printf("No se cargo la textura de la princesa");
  this->princessTexture = texture;
}

void TextureManager::loadErrorTexture() {
  Logger::log(Logger::Info, "Se inicia la carga de textura de error.");
  SDL_Texture *texture = NULL;
  texture = this->loadTexture(".resources/sprites/errortexture.png.");
  if (!texture) {
    Logger::log(Logger::Error,
                "Error al abrir archivo \".resources/sprites/errortexture.png.\". TextureManager::loadErrorTexture");
  }

  this->errorTexture = texture;

}

std::string TextureManager::loadTextureFromJson(char const *spritePath) {
  std::string path = ".resources/sprites/errortexture.png.";
  if (sprites.contains(spritePath)) {
    path = to_string((sprites.at(spritePath)));
  } else {
    std::string message =
            std::string("Error al buscar la clave ") + spritePath + std::string(". Se carga un sprite por defecto.");
    Logger::log(Logger::Error, message);
  }
  return path;
}

SDL_Texture *TextureManager::getPlatformTexture(int levelnum) {
  if (levelnum == 1) {
    return this->bluePlatformTexture;
  }
  return this->redPlatformTexture;
}

SDL_Texture *TextureManager::getLadderTexture(int levelnum) {
  if (levelnum == 1) {
    return this->yellowLadderTexture;
  }
  return this->cyanLadderTexture;
}

SDL_Texture *TextureManager::getFireTexture() {
  return this->fireTexture;
}

SDL_Texture **TextureManager::getPlayersTextures() {
  return this->playersTextures;
}

SDL_Texture *TextureManager::getEnemyTexture() {
  return this->enemyTexture;
}

SDL_Texture *TextureManager::getErrorTexture() {
  return this->errorTexture;
}

SDL_Texture *TextureManager::getBossTexture() {
  return this->bossTexture;
}

SDL_Texture *TextureManager::getPrincessTexture() {
  return this->princessTexture;
}

SDL_Texture *TextureManager::getBarrelTexture() {
  return this->barrelTexture;
}

SDL_Texture *TextureManager::getInactivePlayerTexture() {
    return this->inectivePlayerTexture;
}

void TextureManager::loadInactivePlayerTexture() {
    SDL_Texture *texture = NULL;
    texture = this->loadTexture(this->loadTextureFromJson("inactive_player"));
    if (texture == NULL) printf("No se cargo la textura del jugador inactivo");
    this->inectivePlayerTexture = texture;
}
