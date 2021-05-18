#include "Level.h"
#include "Logger.h"

Level::Level() {
    this->platforms = NULL;
    this->platformCount = 0;
    this->ladders = NULL;
    this->ladderCount = 0;
    this->fires = NULL;
    this->fireCount = 0;
    this->spawns = NULL;
    this->spawnCount = 0;
    this->loader = new LevelLoader();
}

Level::~Level() {
    this->freePlaforms();
    this->freeLadders();
    this->freeFires();
    this->freeSpawns();
    delete this->loader;
}


void Level::loadLevel(int levelnum) {
    this->reset();
    this->loader->loadLevel(levelnum, &this->platforms, &this->ladders, &this->fires, &this->platformCount,
                            &this->ladderCount, &this->fireCount, &this->spawns, &this->spawnCount);

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

void Level::reset() {
    Logger::log(Logger::Debug,"Se reseta el nivel");
    this->freePlaforms();
    this->freeLadders();
    this->freeFires();
    this->freeSpawns();
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


