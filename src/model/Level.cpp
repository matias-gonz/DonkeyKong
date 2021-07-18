#include "Level.h"
#include "Logger.h"
#include "Collider.h"
#include "EnemyFire.h"

Level::Level() {
  this->platforms = NULL;
  this->platformCount = 0;
  this->ladders = NULL;
  this->ladderCount = 0;
  this->fires = NULL;
  this->fireCount = 0;
  this->barrels = NULL;
  this->barrelCount = 0;
  this->spawns = NULL;
  this->spawnCount = 0;
  this->loader = new LevelLoader();
  this->counter = 0;
}

Level::~Level() {
  this->freePlaforms();
  this->freeLadders();
  this->freeFires();
  this->freeSpawns();
  this->freeBarrels();
  delete this->loader;
}


void Level::loadLevel(int levelnum, Configuration *configuration) {
  this->reset();
  this->currentLevel = levelnum;
  this->loader->loadLevel(levelnum, &this->platforms, &this->ladders, &this->fires, &this->platformCount,
                          &this->ladderCount, &this->fireCount, &this->spawns, &this->spawnCount,
                          configuration);

}


int Level::getLadderCount() {
  return ladderCount;
}

void Level::update() {
  for (int i = 0; i < this->platformCount; i++) {
    this->platforms[i]->update();
  }
  for (int i = 0; i < this->fireCount; i++) {
    this->fires[i]->update();
  }
  if(this->currentLevel == 2){
    this->counter += 1;

    if (this->counter > 10){
      this->spawnBarrel();
      this->counter = 0;
    }
    for (int i = 0; i < this->barrelCount; i++) {
      this->barrels[i]->update();
    }
  }
}

Ladder *Level::getLadder(int i) {
  return ladders[i];
}

int Level::getPlatformCount() {
  return platformCount;
}

Platform *Level::getPlatform(int i) {
  return platforms[i];
}

int Level::getFireCount() {
  return fireCount;
}

Fire *Level::getFire(int i) {
  return fires[i];
}

int Level::getBarrelCount() {
  return barrelCount;
}

Barrel *Level::getBarrel(int i) {
  return barrels[i];
}

void Level::reset() {
  Logger::log(Logger::Debug, "Se resetea el nivel");
  this->freePlaforms();
  this->freeLadders();
  this->freeFires();
  this->freeSpawns();
  this->freeBarrels();
  this->platforms = NULL;
  this->platformCount = 0;
  this->ladders = NULL;
  this->ladderCount = 0;
  this->fires = NULL;
  this->fireCount = 0;
  this->barrels = NULL;
  this->barrelCount = 0;
}

void Level::freePlaforms() {
  for (int i = 0; i < this->platformCount; i++) {
    delete this->platforms[i];
  }
  free(this->platforms);
  this->platforms = NULL;
  this->platformCount = 0;
}

void Level::freeLadders() {
  for (int i = 0; i < this->ladderCount; i++) {
    delete this->ladders[i];
  }
  free(this->ladders);
  this->ladders = NULL;
  this->ladderCount = 0;
}

void Level::freeFires() {
  for (int i = 0; i < this->fireCount; i++) {
    delete this->fires[i];
  }
  free(this->fires);
  this->fires = NULL;
  this->fireCount = 0;
}

void Level::freeSpawns() {
  for (int i = 0; i < this->spawnCount; i++) {
    delete this->spawns[i];
  }
  free(this->spawns);
  this->spawns = NULL;
  this->spawnCount = 0;
}

Position **Level::getSpawns() {
  return this->spawns;
}

int Level::getSpawnCount() {
  return this->spawnCount;
}

int Level::getCurrentLevel() {
  return this->currentLevel;
}

void Level::freeBarrels() {
  for (int i; i < this->barrelCount; i++) {
    delete this->barrels[i];
  }
  free(this->barrels);
}

void Level::resolveCollisions(Player **players, int playerCount, EnemyFire **enemyFires, int enemyFireCount, Hammer **hammers, int hammersCount) {
  SDL_Rect *playerRects = (SDL_Rect *) malloc(playerCount * sizeof(SDL_Rect));

  for (int i = 0; i < playerCount; i++) {
    playerRects[i] = players[i]->getRectangle();
  }
  for (int i = 0; i < this->platformCount; i++) {
    SDL_Rect platformRect = this->platforms[i]->getRectangle();
    for (int j = 0; j < playerCount; j++) {
      if (Collider::RectCollides(playerRects[j], platformRect)) {
        Collider::ResolvePlayerCollision(players[j], platformRect);
      }
    }
    for (int j = 0; j < enemyFireCount; j++) {
      SDL_Rect fireRect = enemyFires[j]->getRectangle();
      if (Collider::RectCollides(fireRect, platformRect)) {
        Collider::ResolveEnemyCollision(enemyFires[j], platformRect);
      }
    }

    if(this->currentLevel == 2){
      for(int j = 0; j < barrelCount; j++){
        SDL_Rect *barrelRect = barrels[j]->getDestRect();
        if (Collider::RectCollides(*barrelRect, platformRect)) {
          Collider::ResolveBarrelCollision(barrels[j], platformRect);
        }
      }
    }
  }
  for(int i = 0; i < playerCount; i++){
    for(int j = 0; j < enemyFireCount; j++){
      if (Collider::RectCollides(playerRects[i], enemyFires[j]->getRectangle())) {
        Collider::ResolvePlayerEnemyCollision(players[i], enemyFires[j]);
      }
    }
    for(int j = 0; j < this->fireCount; j++){
      if(Collider::RectCollides(playerRects[i], this->fires[j]->getRectangle())){
        Collider::ResolvePlayerFireCollision(players[i]);
      }
    }

  }

  bool *canClimb = (bool *) malloc(playerCount * sizeof(bool));
  for (int i = 0; i < playerCount; i++) {
    playerRects[i].y += playerRects[i].h / 2;
    playerRects[i].h = playerRects[i].h / 2;
    canClimb[i] = false;
  }

  for (int i = 0; i < this->ladderCount; i++) {
    SDL_Rect ladderRect = this->ladders[i]->getRectangle();
    for (int j = 0; j < playerCount; j++) {
      if (Collider::RectCollides(playerRects[j], ladderRect)) {
        canClimb[j] = true;
      }
    }
  }
  for (int i = 0; i < playerCount; i++) {
    players[i]->setCanClimb(canClimb[i]);
  }

  free(playerRects);
  free(canClimb);

}

bool Level::playerWon(Player *player) {
  if (player->isIn(this->winningPosition)) {
    player->playerWon();
    return true;
  }
  return false;
}

void Level::spawnBarrel() {
  if(this->barrelCount){
    this->barrels = (Barrel**)realloc(this->barrels,(this->barrelCount+1)*sizeof(Barrel*));
    if(!this->barrels){
      Logger::log(Logger::Error,"Error al reservar memoria. Level::spawnBarrel().");
      this->barrelCount = 0;
      return;
    }
  }
  else{
    this->barrels = (Barrel**)malloc(sizeof (Barrel*));
  }
  this->barrels[this->barrelCount] = new Barrel(new Position(100, 35));
  this->barrelCount += 1;

}


