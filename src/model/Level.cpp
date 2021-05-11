#include "Level.h"

Level::Level() {
    this->platforms = NULL;
    this->platformCount = 0;
    this->ladders = NULL;
    this->ladderCount = 0;
    this->fires = NULL;
    this->fireCount = 0;
}
Level::~Level(){
    this->freePlaforms();
    this->freeLadders();
    this->freeFires();
}

void Level::loadPlatforms(int level) {
    char* levelDir = "src/model/levels/level1.txt";
    if(level == 2){
        levelDir = "src/model/levels/level2.txt";
    }
    FILE *file = fopen(levelDir, "r");

    int x, dx, y, dy, count;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        this->platforms = (Platform **) (realloc(this->platforms, (this->platformCount + 1) * sizeof(Platform *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Platform *platform = new Platform(pos, count,false);
        this->platforms[this->platformCount] = platform;
        this->platformCount++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);
}

void Level::loadMovPlatforms(int level) {
    char* levelDir = "src/model/levels/level1moveplat.txt";
    if(level == 2){
        levelDir = "src/model/levels/level2moveplat.txt";
    }
    FILE *file = fopen(levelDir, "r");

    int x, dx, y, dy, count,direction;
    int read = fscanf(file, "%i;%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count, &direction);
    while (read == 6) {
        this->platforms = (Platform **) (realloc(this->platforms, (this->platformCount + 1) * sizeof(Platform *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Platform *platform = new Platform(pos, count,true);
        this->platforms[this->platformCount] = platform;
        this->platformCount++;
        read = fscanf(file, "%i;%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count, &direction);

    }
    fclose(file);
}

void Level::loadStairs(int level) {
    char* levelDir = "src/model/levels/level1stairs.txt";
    if(level == 2){
        levelDir = "src/model/levels/level2stairs.txt";
    }
    FILE *file = fopen(levelDir, "r");

    int x, dx, y, dy, count;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        this->ladders = (Ladder **) (realloc(this->ladders, (this->ladderCount + 1) * sizeof(Ladder *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Ladder* stair = new Ladder(pos,count);
        this->ladders[this->ladderCount] = stair;
        this->ladderCount++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);
}

void Level::loadFire(int level) {
    char* levelDir = "src/model/levels/level1fire.txt";
    if(level == 2){
        levelDir = "src/model/levels/level2fire.txt";
    }
    FILE *file = fopen(levelDir, "r");

    int x, dx, y, dy, count;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        this->fires = (Fire **) (realloc(this->fires, (this->fireCount + 1) * sizeof(Fire *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 32 - dy);
        Fire* fire = new Fire(pos,count);
        this->fires[this->fireCount] = fire;
        this->fireCount++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);
}

void Level::loadLevel(int levelnum) {
    this->reset();
    this->loadPlatforms(levelnum);
    this->loadStairs(levelnum);
    this->loadMovPlatforms(levelnum);
    this->loadFire(levelnum);
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


