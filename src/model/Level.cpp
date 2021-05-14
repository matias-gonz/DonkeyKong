#include "Level.h"

Level::Level() {
    this->platforms = NULL;
    this->platformCount = 0;
    this->ladders = NULL;
    this->ladderCount = 0;
    this->fires = NULL;
    this->fireCount = 0;
    this->barrels = NULL;
    this->barrelCount = 0;
    this->loader = new LevelLoader();
}
Level::~Level(){
    this->freePlatforms();
    this->freeLadders();
    this->freeFires();
    delete this->loader;
}


void Level::loadLevel(int levelnum) {
    this->reset();
    this->loader->loadLevel(levelnum,&this->platforms,&this->ladders,&this->fires, &this->barrels, &this->platformCount,&this->ladderCount,&this->fireCount, &this->barrelCount);

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
    this->freePlatforms();
    this->freeLadders();
    this->freeFires();
    this->freeBarrels();
    this->platforms = NULL;
    this->platformCount = 0;
    this->ladders = NULL;
    this->ladderCount = 0;
    this->fires = NULL;
    this->fireCount = 0;
}

void Level::freePlatforms() {
    for(int i; i < this->platformCount; i++){
        delete this->platforms[i];
    }
    free(this->platforms);
}

void Level::freeLadders() {
    for(int i; i < this->ladderCount; i++){
        delete this->ladders[i];
    }
    free(this->ladders);
}

void Level::freeFires() {
    for(int i; i < this->fireCount; i++){
        delete this->fires[i];
    }
    free(this->fires);
}

void Level::freeBarrels() {
    for(int i; i < this->barrelCount; i++){
        delete this->barrels[i];
    }
    free(this->barrels);
}


