#include "Level.h"

#include "../view/TextureManager.h"

Level::Level() {
    this->platforms = NULL;
    this->platformCount = 0;
    this->platformTexture = TextureManager::LoadTexture("/home/matiti/Documents/Taller1/Taller-Prog-I-2021-1C-KIWI/resources/sprites/platform.png");
}

void Level::loadLevel() {
    FILE* file = fopen("/home/matiti/Documents/Taller1/Taller-Prog-I-2021-1C-KIWI/src/model/levels/level2.txt","r");

    int x,dx,y,dy,count;
    int read = fscanf(file,"%i;%i;%i;%i;%i\n",&x,&dx,&y,&dy,&count);
    while(read == 5){
        this->platforms = (Platform **)(realloc(this->platforms, (this->platformCount + 1 ) * sizeof(Platform *)));
        Position pos;
        pos.x = x*32 + dx;
        pos.y = HEIGHT-(1+y)*21 - dy;
        Platform* platform = new Platform(pos,count);
        this->platforms[this->platformCount] = platform;
        this->platformCount++;
        read = fscanf(file,"%i;%i;%i;%i;%i\n",&x,&dx,&y,&dy,&count);
    }
}

void Level::drawLevel() {

    for(int i = 0; i < this->platformCount; i++){
        this->platforms[i]->draw(this->platformTexture);
    }
}
