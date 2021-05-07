#include "Level.h"

Level::Level() {
    this->platforms = NULL;
    this->platformCount = 0;
    this->platformTexture = TextureManager::LoadTexture(
            "resources/sprites/blueplat.png");
    this->stairs = NULL;
    this->stairCount = 0;
    this->stairTexture = TextureManager::LoadTexture("resources/sprites/yelstair.png");
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
        printf("x: %f\ny: %f\n\n",pos.getX(),pos.getY());
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

void Level::loadLevel() {
    this->loadPlatforms();
    this->loadStairs();
    this->loadMovPlatforms();
}

void Level::drawLevel() {

    for(int i = 0; i < this->stairCount; i++){
        this->stairs[i]->draw(this->stairTexture);
    }
    for (int i = 0; i < this->platformCount; i++) {
        this->platforms[i]->draw(this->platformTexture);
    }

}

void Level::update(){
    for (int i = 0; i < this->platformCount; i++) {
        this->platforms[i]->update();
    }
}
