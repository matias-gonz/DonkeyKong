#include "Level.h"
#include "Logger.h"

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
}

Level::~Level() {
    this->freePlaforms();
    this->freeLadders();
    this->freeFires();
    this->freeSpawns();
    this->freeBarrels();
    delete this->loader;
}


void Level::loadLevel(int levelnum, Configuration* configuration) {
    this->reset();
    this->currentLevel = levelnum;
    this->loader->loadLevel(levelnum, &this->platforms, &this->ladders, &this->fires,&this->barrels, &this->platformCount,
                            &this->ladderCount, &this->fireCount, &this->barrelCount, &this->spawns, &this->spawnCount,
                            configuration);

}

int Level::getLadderCount() {
    return ladderCount;
}

void Level::update(){
    for (int i = 0; i < this->platformCount; i++) {
        this->platforms[i]->update();
    }
    for (int i = 0; i < this->fireCount; i++) {
        this->fires[i]->update();
    }
    for (int i = 0; i < this->barrelCount; i++) {
        this->barrels[i]->update();
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
    Logger::log(Logger::Debug,"Se reseta el nivel");
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
    for(int i; i < this->barrelCount; i++){
        delete this->barrels[i];
    }
    free(this->barrels);
}


