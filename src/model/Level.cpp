#include "Level.h"
#include "../view/TextureManager.h"

Level::Level() {

}

void Level::loadLevel() {
    Position pos;
    Platform* platform = new Platform(pos,1);
    this->platforms = platform;
    this->platformCount = 1;
    this->platformTexture = TextureManager::LoadTexture("/home/matiti/Documents/Taller1/Taller-Prog-I-2021-1C-KIWI/resources/sprites/platform.png");
}

void Level::drawLevel() {

    for(int i = 0; i < this->platformCount; i++){
        this->platforms[i].draw(this->platformTexture);
    }
}