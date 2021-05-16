#include "Level.h"

Level::Level() {
    this->platforms = NULL;
    this->platformCount = 0;
    this->ladders = NULL;
    this->ladderCount = 0;
    this->fires = NULL;
    this->fireCount = 0;
    this->loader = new LevelLoader();
}

Level::~Level() {
    this->freePlaforms();
    this->freeLadders();
    this->freeFires();
    delete this->loader;
}


void Level::loadLevel(int levelnum) {
    this->reset();
    this->loader->loadLevel(levelnum, &this->platforms, &this->ladders, &this->fires, &this->platformCount,
                            &this->ladderCount, &this->fireCount);

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
    this->freePlaforms();
    this->freeLadders();
    this->freeFires();
    this->platforms = NULL;
    this->platformCount = 0;
    this->ladders = NULL;
    this->ladderCount = 0;
    this->fires = NULL;
    this->fireCount = 0;
}

void Level::freePlaforms() {
    for (int i = 0; i < this->platformCount; i++) {
        delete this->platforms[i];
    }
    free(this->platforms);
}

void Level::freeLadders() {
    for (int i = 0; i < this->ladderCount; i++) {
        delete this->ladders[i];
    }
    free(this->ladders);
}

void Level::freeFires() {
    for (int i = 0; i < this->fireCount; i++) {
        delete this->fires[i];
    }
    free(this->fires);
}


