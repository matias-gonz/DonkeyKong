#include <iomanip>
#include <iostream>
#include "LevelLoader.h"

LevelLoader::LevelLoader() {}

LevelLoader::~LevelLoader() {}

void LevelLoader::loadLevel(int level, Platform ***platforms, Ladder ***ladders, Fire ***fires, Barrel ***barrels, int *platformCount,
                            int *ladderCount, int *fireCount, int *barrelCount) {

    //this->writeJSON();
    json jsonLevel;
    if(level == 1){
        std::ifstream i("src/model/levels/level1.json");
        i >> jsonLevel;
    }else if(level == 2){
        std::ifstream i("src/model/levels/level2.json");
        i >> jsonLevel;
    }

    *platforms = this->loadPlatforms(jsonLevel,platformCount);
    *ladders = this->loadLadders(jsonLevel,ladderCount);
    *fires = this->loadFire(jsonLevel,fireCount);
    *barrels = this->loadBarrel(jsonLevel, barrelCount);
}



Platform** LevelLoader::loadPlatforms(json jsonLevel, int* platformCount) {

    Platform** tmpPlatforms = NULL;
    int x, dx, y, dy, count, direction;
    for (const auto& item : jsonLevel["platforms"].items())
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
        Platform *platform = new Platform(pos, count,direction);
        tmpPlatforms[*platformCount] = platform;
        (*platformCount)++;

    }
    return tmpPlatforms;

}

Ladder** LevelLoader::loadLadders(json jsonLevel, int *ladderCount) {

    Ladder** tmpLadders = NULL;
    int x, dx, y, dy, count;
    for (const auto& item : jsonLevel["ladders"].items()){
        x = item.value()["x"];
        dx = item.value()["dx"];
        y = item.value()["y"];
        dy = item.value()["dy"];
        count = item.value()["count"];
        tmpLadders = (Ladder **) (realloc(tmpLadders, (*ladderCount + 1) * sizeof(Ladder *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 21 - dy);
        Ladder *ladder = new Ladder(pos, count);
        tmpLadders[*ladderCount] = ladder;
        (*ladderCount)++;

    }
    return tmpLadders;
}

Fire** LevelLoader::loadFire(json jsonLevel, int *fireCount) {
    Fire** tmpFires = NULL;

    int x, dx, y, dy, count;
    for (const auto& item : jsonLevel["fires"].items()){
        x = item.value()["x"];
        dx = item.value()["dx"];
        y = item.value()["y"];
        dy = item.value()["dy"];
        count = item.value()["count"];

        tmpFires = (Fire **) (realloc(tmpFires, (*fireCount + 1) * sizeof(Fire *)));
        Position pos;
        pos.setX(x * 32 + dx);
        pos.setY(HEIGHT - (1 + y) * 32 - dy);
        Fire* fire = new Fire(pos,count);
        tmpFires[*fireCount] = fire;
        (*fireCount)++;
    }
    return tmpFires;
}

Barrel** LevelLoader::loadBarrel(json jsonLevel, int *barrelCount){

    Barrel** tmpBarrel = NULL;
    int x, dx, y, dy, count, direction;
    for (const auto& item : jsonLevel["barrels"].items())
    {
        x = item.value()["x"];
        dx = item.value()["dx"];
        y = item.value()["y"];
        dy = item.value()["dy"];
        count = item.value()["count"];
        direction = item.value()["direction"];

        tmpBarrel = (Barrel **) (realloc(tmpBarrel, (*barrelCount + 1) * sizeof(Barrel *)));
        Position pos;
        pos.setX(x);
        pos.setY(y );
        Barrel *barrel = new Barrel(pos, count,direction);
        tmpBarrel[*barrelCount] = barrel;
        (*barrelCount)++;

    }
    return tmpBarrel;
}

/*
void LevelLoader::writeJSON() {
    FILE *file = fopen("src/model/levels/level2.txt", "r");
    json jLevel1;

    std::string s;
    int countObj = 0;

    int x, dx, y, dy, count,direction;
    int read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        s = std::to_string(countObj);
        jLevel1["platforms"][s]["x"] = x;
        jLevel1["platforms"][s]["dx"] = dx;
        jLevel1["platforms"][s]["y"] = y;
        jLevel1["platforms"][s]["dy"] = dy;
        jLevel1["platforms"][s]["count"] = count;
        jLevel1["platforms"][s]["direction"] = 0;

        countObj++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);

    file = fopen("src/model/levels/level2moveplat.txt", "r");
    read = fscanf(file, "%i;%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count,&direction);
    while (read == 6) {
        s = std::to_string(countObj);
        jLevel1["platforms"][s]["x"] = x;
        jLevel1["platforms"][s]["dx"] = dx;
        jLevel1["platforms"][s]["y"] = y;
        jLevel1["platforms"][s]["dy"] = dy;
        jLevel1["platforms"][s]["count"] = count;
        jLevel1["platforms"][s]["direction"] = direction;

        countObj++;
        read = fscanf(file, "%i;%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count,&direction);
    }
    fclose(file);

    countObj = 0;
    file = fopen("src/model/levels/level2stairs.txt", "r");
    read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        s = std::to_string(countObj);
        jLevel1["ladders"][s]["x"] = x;
        jLevel1["ladders"][s]["dx"] = dx;
        jLevel1["ladders"][s]["y"] = y;
        jLevel1["ladders"][s]["dy"] = dy;
        jLevel1["ladders"][s]["count"] = count;

        countObj++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);

    countObj = 0;
    file = fopen("src/model/levels/level2fire.txt", "r");
    read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    while (read == 5) {
        s = std::to_string(countObj);
        jLevel1["fires"][s]["x"] = x;
        jLevel1["fires"][s]["dx"] = dx;
        jLevel1["fires"][s]["y"] = y;
        jLevel1["fires"][s]["dy"] = dy;
        jLevel1["fires"][s]["count"] = count;

        countObj++;
        read = fscanf(file, "%i;%i;%i;%i;%i\n", &x, &dx, &y, &dy, &count);
    }
    fclose(file);


    std::ofstream o("src/model/levels/level2.json");
    o << std::setw(4) << jLevel1 << std::endl;
}

*/