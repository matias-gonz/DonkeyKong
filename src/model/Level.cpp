#include "Level.h"

Level::Level() {
    this->platforms = NULL;
    this->platformCount = 0;
    this->platformTexture = TextureManager::LoadTexture(
            "resources/sprites/blueplat.png");
    this->stairs = NULL;
    this->stairCount = 0;
    this->stairTexture = TextureManager::LoadTexture("resources/sprites/yelstair.png");
    this->fires = NULL;
    this->fireCount = 0;
    this->fireTexture = TextureManager::LoadTexture("resources/sprites/fire.png");
}

void Level::loadPlatforms(){
    FILE *file = fopen("src/model/levels/level1.txt", "r");

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

void Level::loadMovPlatforms(){
    FILE *file = fopen("src/model/levels/level1moveplat.txt", "r");

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

void Level::loadFire() {
    FILE *file = fopen("src/model/levels/level1fire.txt", "r");

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

void Level::loadLevel() {
    this->loadPlatforms();
    this->loadStairs();
    this->loadMovPlatforms();
    this->loadFire();
}

void Level::drawLevel() {

    for(int i = 0; i < this->stairCount; i++){
        this->stairs[i]->draw(this->stairTexture);
    }
    for (int i = 0; i < this->platformCount; i++) {
        this->platforms[i]->draw(this->platformTexture);
    }
    for (int i = 0; i < this->fireCount; i++) {
        this->fires[i]->draw(this->fireTexture);
    }

}

void Level::update(){
    for (int i = 0; i < this->platformCount; i++) {
        this->platforms[i]->update();
    }
    for (int i = 0; i < this->fireCount; i++) {
        this->fires[i]->update();
    }
}


