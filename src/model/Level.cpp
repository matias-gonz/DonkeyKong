#include "Level.h"

Level::Level() {
    this->platforms = NULL;
    this->platformCount = 0;
    this->stairs = NULL;
    this->stairCount = 0;
}

void Level::loadPlatforms(){
    FILE *file = fopen("src/model/levels/level2.txt", "r");

    int x, dx, y, dy, count;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        this->platforms = (Platform **) (realloc(this->platforms, (this->platformCount + 1) * sizeof(Platform *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Platform *platform = new Platform(pos, count);
        this->platforms[this->platformCount] = platform;
        this->platformCount++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);
}

void Level::loadMovPlatforms(){
    FILE *file = fopen("src/model/levels/level1moveplat.txt", "r");

    int x, dx, y, dy, count,direction;
    int read = fscanf(file, "%i;%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count, &direction);
    while (read == 6) {
        this->platforms = (Platform **) (realloc(this->platforms, (this->platformCount + 1) * sizeof(Platform *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Platform *platform = new Platform(pos, count);
        this->platforms[this->platformCount] = platform;
        this->platformCount++;
        read = fscanf(file, "%i;%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count, &direction);
    }
    fclose(file);
}

void Level::loadStairs(){
    FILE *file = fopen("src/model/levels/level1stairs.txt", "r");

    int x, dx, y, dy, count;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        this->stairs = (Ladder **) (realloc(this->stairs, (this->stairCount + 1) * sizeof(Ladder *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Ladder* stair = new Ladder(pos,count);
        this->stairs[this->stairCount] = stair;
        this->stairCount++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);
}

void Level::loadLevel() {
    this->loadPlatforms();
    this->loadStairs();
    this->loadMovPlatforms();
}

int Level::getStairCount() {
    return stairCount;
}

Ladder *Level::getLedder(int i) {
    return stairs[i];
}

int Level::getPlatformCount() {
    return platformCount;
}

Platform *Level::getPlatform(int i) {
    return platforms[i];
}


