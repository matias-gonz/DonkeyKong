#include "Level.h"



Level::Level() {
    this->platforms = NULL;
    this->platformCount = 0;
    this->platformTexture = TextureManager::LoadTexture(
            "resources/sprites/redplat.png");
    this->stairs = NULL;
    this->stairCount = 0;
    this->stairTexture = TextureManager::LoadTexture("resources/sprites/stair.png");
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
}

void Level::loadStairs(){
    FILE *file = fopen("src/model/levels/level2stairs.txt", "r");

    int x, dx, y, dy, count;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        this->stairs = (Stair **) (realloc(this->stairs, (this->stairCount + 1) * sizeof(Stair *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Stair* stair = new Stair(pos,count);
        this->stairs[this->stairCount] = stair;
        this->stairCount++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }

}

void Level::loadLevel() {
    this->loadPlatforms();
    this->loadStairs();
}

void Level::drawLevel() {

    for(int i = 0; i < this->stairCount; i++){
        this->stairs[i]->draw(this->stairTexture);
    }
    for (int i = 0; i < this->platformCount; i++) {
        this->platforms[i]->draw(this->platformTexture);
    }

}
