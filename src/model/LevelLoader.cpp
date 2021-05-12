#include "LevelLoader.h"

LevelLoader::LevelLoader() {}

LevelLoader::~LevelLoader() {}

void LevelLoader::loadLevel(int level, Platform ***platforms, Ladder ***ladders, Fire ***fires, int *platformCount,
                            int *ladderCount, int *fireCount) {
    char* levelDir = "src/model/levels/level1.txt";
    char* ladderDir = "src/model/levels/level1stairs.txt";
    char* fireDir = "src/model/levels/level1fire.txt";
    if(level == 2){
        levelDir = "src/model/levels/level2.txt";
        ladderDir = "src/model/levels/level2stairs.txt";
        fireDir = "src/model/levels/level2fire.txt";
    }

    *platforms = this->loadPlatforms(levelDir,platformCount);
    *ladders = this->loadLadders(ladderDir,ladderCount);
    *fires = this->loadFire(fireDir,fireCount);
}

Platform** LevelLoader::loadPlatforms(char* levelDir, int* platformCount) {

    FILE *file = fopen(levelDir, "r");
    Platform** tmpPlatforms = NULL;

    int x, dx, y, dy, count;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        tmpPlatforms = (Platform **) (realloc(tmpPlatforms, (*platformCount + 1) * sizeof(Platform *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Platform *platform = new Platform(pos, count,false);
        tmpPlatforms[*platformCount] = platform;
        (*platformCount)++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);
    return tmpPlatforms;
}

Ladder** LevelLoader::loadLadders(char* levelDir, int *ladderCount) {
    FILE *file = fopen(levelDir, "r");
    Ladder** tmpLadders = NULL;

    int x, dx, y, dy, count;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        tmpLadders = (Ladder **) (realloc(tmpLadders, (*ladderCount + 1) * sizeof(Ladder *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Ladder* ladder = new Ladder(pos,count);
        tmpLadders[*ladderCount] = ladder;
        (*ladderCount)++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);
    return tmpLadders;
}

Fire** LevelLoader::loadFire(char* levelDir, int *fireCount) {
    FILE *file = fopen(levelDir, "r");

    Fire** tmpFires = NULL;

    int x, dx, y, dy, count;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        tmpFires = (Fire **) (realloc(tmpFires, (*fireCount + 1) * sizeof(Fire *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 32 - dy);
        Fire* fire = new Fire(pos,count);
        tmpFires[*fireCount] = fire;
        (*fireCount)++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);
    return tmpFires;
}