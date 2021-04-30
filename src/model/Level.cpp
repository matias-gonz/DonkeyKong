#include "Level.h"
#include<string>

Level::Level(string dir) {
    setPlatforms(dir);
}

Platform* Level::getPlatforms() {
    return platforms;
}

int Level::getCount() {
    return count;
}

void Level::setPlatforms(string dir) {
    platforms = NULL;
    count = 0;
}
