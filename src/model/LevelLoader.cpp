#include <iomanip>
#include <iostream>
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

    this->writeJSON();
    *platforms = this->loadPlatforms(levelDir,platformCount);
    *ladders = this->loadLadders(ladderDir,ladderCount);
    *fires = this->loadFire(fireDir,fireCount);
}

void LevelLoader::writeJSON() {
    FILE *file = fopen("src/model/levels/level1.txt", "r");
    json j;

    std::string s;
    int countObj = 0;

    int x, dx, y, dy, count,direction;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        s = std::to_string(countObj);
        j["platforms"][s]["x"] = x;
        j["platforms"][s]["dx"] = dx;
        j["platforms"][s]["y"] = y;
        j["platforms"][s]["dy"] = dy;
        j["platforms"][s]["count"] = count;
        j["platforms"][s]["direction"] = 0;

        countObj++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);
    file = fopen("src/model/levels/level1moveplat.txt", "r");
    read = fscanf(file, "%i;%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count,&direction);
    while (read == 6) {
        s = std::to_string(countObj);
        j["platforms"][s]["x"] = x;
        j["platforms"][s]["dx"] = dx;
        j["platforms"][s]["y"] = y;
        j["platforms"][s]["dy"] = dy;
        j["platforms"][s]["count"] = count;
        j["platforms"][s]["direction"] = direction;

        countObj++;
        read = fscanf(file, "%i;%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count,&direction);
    }
    fclose(file);
    std::ofstream o("src/model/levels/level1.json");
    o << std::setw(4) << j << std::endl;
}

Platform** LevelLoader::loadPlatforms(char* levelDir, int* platformCount) {

    std::ifstream i("src/model/levels/level1.json");
    json j;
    i >> j;

    Platform** tmpPlatforms = NULL;
    int x, dx, y, dy, count, direction;
    for (const auto& item : j["platforms"].items())
    {
        x = item.value()["x"];
        dx = item.value()["dx"];
        y = item.value()["y"];
        dy = item.value()["dy"];
        count = item.value()["count"];
        direction = item.value()["direction"];

        tmpPlatforms = (Platform **) (realloc(tmpPlatforms, (*platformCount + 1) * sizeof(Platform *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Platform *platform = new Platform(pos, count,false);
        tmpPlatforms[*platformCount] = platform;
        (*platformCount)++;

    }
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