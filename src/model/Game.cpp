#include "Game.h"

Game::Game(Configuration *configuration) {
  this->configuration = configuration;
}

Game::~Game() {
  for (int i = 0; i < this->playerCount; i++) {
    delete this->players[i];
  }
  free(this->players);
  delete this->level;
  for (int i = 0; i < this->enemyFireCount; i++) {
    delete this->enemyFires[i];
  }
  free(this->enemyFires);

  for (int i = 0; i < this->hammersCount; i++) {
    delete this->hammers[i];
  }
  free(this->hammers);
}

void Game::start() {
  this->running = true;
  this->level = new Level();
  this->players = NULL;
  this->playerCount = 0;
  this->loadLevel(1);

  Logger::log(Logger::Info, "Inicio Donkey Kong");
  this->boss = new Boss(new Position(100, 85));
  this->princess = new Princess(new Position(450, 80));
}

void Game::quit() {
  running = false;
}

void Game::update() {
  if (this->everyPlayerWon()) {
    for (int i = 0; i < playerCount; i++) {
      this->players[i]->resetPlayerWon();
    }
    this->switchLevel();
    return;
  }
  this->level->update();
  for (int i = 0; i < this->playerCount; i++) {
    this->players[i]->update();
  }
  for (int i = 0; i < this->enemyFireCount; i++) {
    this->enemyFires[i]->update();
  }
  for (int i = 0; i < this->hammersCount; i++) {
    this->hammers[i]->update();
  }

  this->princess->update();
  this->boss->update();
  this->resolveCollisions();
}

bool Game::isRunning() {
  return this->running;
}

Level *Game::getLevel() {
  return this->level;
}

Player *Game::getPlayer(int i) {
  return this->players[i];
}

void Game::loadLevel(int levelnum) {
  this->currentLevel = levelnum;
  this->level->loadLevel(levelnum, this->configuration);
  this->resetEnemies();
  this->resetHammers();
  //level should spawn enemies, not game
  this->spawnEnemies(this->level->getSpawns(), this->level->getSpawnCount(), this->configuration->getEnemiesCount());
  this->spawnHammers(this->level->getSpawns(), this->level->getSpawnCount(), this->configuration->getHammersCount());
}

void Game::spawnEnemies(Position **spawns, int spawnCount, int probability) {
  Logger::log(Logger::Info, "Se spawnean enemigos type_1");
  srand(time(NULL));
  for (int i = 0; i < spawnCount; i++) {
    if ((rand() % 100) < probability) {
      this->enemyFires = (EnemyFire **) (realloc(this->enemyFires, (this->enemyFireCount + 1) * sizeof(EnemyFire *)));
      if (!this->enemyFires) {
        Logger::log(Logger::Error, "Error al reservar memoria. Game::spawnEnemies");
        return;
      }
      EnemyFire *enemy = new EnemyFire(spawns[i]);
      this->enemyFires[this->enemyFireCount] = enemy;
      (this->enemyFireCount)++;
    }
  }
}

void Game::spawnHammers(Position **spawns, int spawnCount, int probability) {
  Logger::log(Logger::Info, "Se spawnean los martillos");
  srand(time(NULL));
  for (int i = 0; i < spawnCount; i++) {
    if ((rand() % 100) < probability) {
      this->hammers = (Hammer **) (realloc(this->hammers, (this->hammersCount + 1) * sizeof(Hammer *)));
      if (!this->hammers) {
        Logger::log(Logger::Error, "Error al reservar memoria. Game::spawnHammers");
        return;
      }
      //spawns[i]->add(0,50);
      Hammer *hammer = new Hammer(spawns[i]);
      //spawns[i]->add(0,-50);
      this->hammers[this->hammersCount] = hammer;
      (this->hammersCount)++;
    }
  }
}

EnemyFire **Game::getEnemyFires() {
  return this->enemyFires;
}

int Game::getEnemyFireCount() {
  return this->enemyFireCount;
}

void Game::resetEnemies() {
  for (int i = 0; i < this->enemyFireCount; i++) {
    delete this->enemyFires[i];
  }
  free(this->enemyFires);
  this->enemyFires = NULL;
  this->enemyFireCount = 0;
}

void Game::resetHammers() {
  for (int i = 0; i < this->hammersCount; i++) {
    delete this->hammers[i];
  }
  free(this->hammers);
  this->hammers = NULL;
  this->hammersCount = 0;
}

void Game::switchLevel() {
  for (int i = 0; i < this->playerCount; i++) {
    this->players[i]->resetPos();
  }
  if (this->currentLevel == 1) {
    this->loadLevel(2);
  } else {
    this->loadLevel(1);
  }
}

Boss *Game::getBoss() {
  return this->boss;
}

Princess *Game::getPrincess() {
  return this->princess;
}

void Game::resolveCollisions() {
  this->level->resolveCollisions(this->players, this->playerCount, this->enemyFires, this->enemyFireCount,
                                 this->hammers, this->hammersCount);

}

void Game::addPlayer(char username[20]) {
  this->players = (Player **) realloc(this->players, (this->playerCount + 1) * sizeof(Player *));
  this->players[this->playerCount] = new Player(new Position(200, 575), username);
  this->playerCount++;
}

void Game::getPlatforms(PlatformContainer *platforms, int *count) {
  *count = this->level->getPlatformCount();
  Platform *tmpPlatform;
  SDL_Rect *tmp;
  for (int i = 0; i < *count; i++) {
    tmpPlatform = this->level->getPlatform(i);
    platforms[i].dest = *tmpPlatform->getDestRect();
    platforms[i].count = tmpPlatform->getCount();
  }
}

void Game::getLadders(LadderContainer *ladders, int *count) {
  *count = this->level->getLadderCount();
  Ladder *tmpLadder;
  SDL_Rect *tmp;
  for (int i = 0; i < *count; i++) {
    tmpLadder = this->level->getLadder(i);
    ladders[i].dest = *tmpLadder->getDestRect();
    ladders[i].count = tmpLadder->getCount();
  }
}

void Game::getFires(FireContainer *fires, int *count) {
  *count = this->level->getFireCount();
  Fire *tmpFire;
  SDL_Rect *tmp;
  for (int i = 0; i < *count; i++) {
    tmpFire = this->level->getFire(i);
    fires[i].src = *tmpFire->getSrcRect();
    fires[i].dest = *tmpFire->getDestRect();
    fires[i].count = tmpFire->getCount();
  }
}

void Game::getEnemyFiresPos(EntityContainer *enemyFires, int *count) {
  *count = this->enemyFireCount;
  for (int i = 0; i < *count; i++) {
    this->getEntityInfo(&enemyFires[i], this->enemyFires[i]);
  }
}

void Game::getBarrelsInfo(EntityContainer *barrels, int *barrelCount) {
  if (this->level->getCurrentLevel() == 2) {
    *barrelCount = this->level->getBarrelCount();
    for (int i = 0; i < *barrelCount; i++) {
      this->getEntityInfo(&barrels[i], this->level->getBarrel(i));
    }
  }
}

void Game::getHammersInfo(EntityContainer *hammers, int *hammersCount) {
  *hammersCount = this->hammersCount;
  for (int i = 0; i < *hammersCount; i++) {
    this->getEntityInfo(&hammers[i], this->hammers[i]);
  }
}

void Game::getPLayerInfo(PlayersInformation *playerInfo, int *playerCount) {
  for (int i = 0; i < this->playerCount; i++) {
    playerInfo[i].distance = players[i]->getDistance();
    playerInfo[i].x = players[i]->getXPosition();
    playerInfo[i].y = players[i]->getYPosition();
    playerInfo[i].direction = players[i]->getDirection();
    playerInfo[i].isActive = players[i]->isPlaying();
    strcpy(playerInfo[i].username, players[i]->getUsername());
    playerInfo[i].hp = players[i]->getHp();
    playerInfo[i].points = players[i]->getPoints();
  }
  *playerCount = this->playerCount;
}

void Game::getBossInfo(EntityContainer *bossInfo) {
  this->getEntityInfo(bossInfo, this->boss);
}

void Game::getPrincessInfo(EntityContainer *princessInfo) {
  this->getEntityInfo(princessInfo, this->princess);
}

void Game::getEntityInfo(EntityContainer *entityInfo, Entity *entity) {
  if (!entity) {
    return;
  }
  entityInfo->distance = entity->getDistance();
  entityInfo->x = entity->getXPosition();
  entityInfo->y = entity->getYPosition();
  entityInfo->direction = entity->getDirection();
}


bool Game::anyPlayerWon() {
  for (int i = 0; i < this->playerCount; i++) {
    if (this->level->playerWon(this->players[i])) {
      return true;
    }
  }
  return false;
}

bool Game::everyPlayerWon() {
  int playersCountWon = 0;
  for (int i = 0; i < this->playerCount; i++) {
    if (this->level->playerWon(this->players[i])) {
      playersCountWon++;
    }
  }
  return playersCountWon == this->playerCount;
}

int Game::getPlayerCount() {
  return this->playerCount;
}

void Game::updateStatus() {
  int playerActive = 0;
  for (int i = 0; i < this->playerCount; i++) {
    if (players[i]->isPlaying()) playerActive++;
  }
  if (playerActive == 0) this->quit();
}

bool Game::isPlayerActive(int playerNumber) {
  return players[playerNumber]->isPlaying();
}

int Game::getCurrentLevel() {
  return currentLevel;
}
