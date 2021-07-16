#include <iomanip>
#include <iostream>

#include "LevelLoader.h"
#include "Logger.h"


LevelLoader::LevelLoader() {}

LevelLoader::~LevelLoader() {}

void LevelLoader::loadLevel(int level, Platform ***platforms, Ladder ***ladders, Fire ***fires, int *platformCount,
                            int *ladderCount, int *fireCount, Position ***spawns, int *spawnCount,
                            Configuration *configuration) {

  json levels = configuration->getLevels();
  //this->writeJSON();
  json jsonLevel;
  if (level == 1) {
    std::string level1 = this->loadLevelFromJson("level1", levels);
    level1.replace(0, 1, "");
    level1.erase(level1.size() - 1);
    Logger::log(Logger::Info, "Se inicia la carga del nivel 1.");
    std::ifstream i(level1);
    if (!i) {
      Logger::log(Logger::Error, "Error al abrir archivo \"src/model/levels/level1.json\". LevelLoader::loadLevel");
      return;
    }
    i >> jsonLevel;
  } else if (level == 2) {
    std::string level2 = this->loadLevelFromJson("level2", levels);
    level2.replace(0, 1, "");
    level2.erase(level2.size() - 1);
    Logger::log(Logger::Info, "Se inicia la carga del nivel 2.");
    std::ifstream i(level2);
    if (!i) {
      Logger::log(Logger::Error, "Error al abrir archivo \"src/model/levels/level2.json\". LevelLoader::loadLevel");
      return;
    }
    i >> jsonLevel;
  }

  *platforms = this->loadPlatforms(jsonLevel, platformCount);
  *ladders = this->loadLadders(jsonLevel, ladderCount);
  *fires = this->loadFire(jsonLevel, fireCount);
  *spawns = this->loadSpawns(jsonLevel, spawnCount);
  Logger::log(Logger::Info, "Se finaliza la carga del nivel.");
}

std::string LevelLoader::loadLevelFromJson(char const *level, json levels) {
  std::string path = ".src/model/levels/level1.json.";
  if (levels.contains(level)) {
    path = to_string(levels.at(level));
  } else {
    std::string message =
            std::string("Error al buscar la clave ") + level + std::string(". Se carga por defecto el nivel 1");
    Logger::log(Logger::Error, message);
  }
  return path;
}

Platform **LevelLoader::loadPlatforms(json jsonLevel, int *platformCount) {
  Logger::log(Logger::Info, "Se inicia la carga de Platform.");
  Platform **tmpPlatforms = NULL;
  int x, dx, y, dy, count, direction;
  for (const auto &item : jsonLevel["platforms"].items()) {
    x = item.value()["x"];
    dx = item.value()["dx"];
    y = item.value()["y"];
    dy = item.value()["dy"];
    count = item.value()["count"];
    direction = item.value()["direction"];

    tmpPlatforms = (Platform **) (realloc(tmpPlatforms, (*platformCount + 1) * sizeof(Platform *)));
    if (!tmpPlatforms) {
      Logger::log(Logger::Error, "Error al reservar memoria. LevelLoader::loadPlatforms");
      *platformCount = 0;
      return NULL;
    }

    Position pos;
    pos.setX(x * 32 + dx);
    pos.setY(HEIGHT - (1 + y) * 24 - dy);
    Platform *platform = new Platform(pos, count, direction);
    tmpPlatforms[*platformCount] = platform;
    (*platformCount)++;

  }
  return tmpPlatforms;

}

Ladder **LevelLoader::loadLadders(json jsonLevel, int *ladderCount) {
  Logger::log(Logger::Info, "Se inicia la carga de Ladder.");
  Ladder **tmpLadders = NULL;
  int x, dx, y, dy, count;
  for (const auto &item : jsonLevel["ladders"].items()) {
    x = item.value()["x"];
    dx = item.value()["dx"];
    y = item.value()["y"];
    dy = item.value()["dy"];
    count = item.value()["count"];
    tmpLadders = (Ladder **) (realloc(tmpLadders, (*ladderCount + 1) * sizeof(Ladder *)));
    if (!tmpLadders) {
      Logger::log(Logger::Error, "Error al reservar memoria. LevelLoader::loadLadders");
      *ladderCount = 0;
      return NULL;
    }
    Position pos;
    pos.setX(x * 32 + dx);
    pos.setY(HEIGHT - (1 + y) * 24 - dy);
    Ladder *ladder = new Ladder(pos, count);
    tmpLadders[*ladderCount] = ladder;
    (*ladderCount)++;

  }
  return tmpLadders;
}

Fire **LevelLoader::loadFire(json jsonLevel, int *fireCount) {
  Logger::log(Logger::Info, "Se inicia la carga de Fire.");
  Fire **tmpFires = NULL;

  int x, dx, y, dy, count;
  for (const auto &item : jsonLevel["fires"].items()) {
    x = item.value()["x"];
    dx = item.value()["dx"];
    y = item.value()["y"];
    dy = item.value()["dy"];
    count = item.value()["count"];

    tmpFires = (Fire **) (realloc(tmpFires, (*fireCount + 1) * sizeof(Fire *)));
    if (!tmpFires) {
      Logger::log(Logger::Error, "Error al reservar memoria. LevelLoader::loadFire");
      *fireCount = 0;
      return NULL;
    }
    Position pos;
    pos.setX(x * 32 + dx);
    pos.setY(HEIGHT - (1 + y) * 32 - dy);
    Fire *fire = new Fire(pos, count);
    tmpFires[*fireCount] = fire;
    (*fireCount)++;
  }
  return tmpFires;
}

Position **LevelLoader::loadSpawns(json jsonLevel, int *spawnCount) {
  Logger::log(Logger::Info, "Se inicia la carga de Spawnpoints.");
  Position **tmpSpawns = NULL;

  int x, dx, y, dy, count;
  for (const auto &item : jsonLevel["spawnpoints"].items()) {
    x = item.value()["x"];
    dx = item.value()["dx"];
    y = item.value()["y"];
    dy = item.value()["dy"];
    count = item.value()["count"];

    for (int i = 0; i < count; i++) {
      tmpSpawns = (Position **) (realloc(tmpSpawns, (*spawnCount + 1) * sizeof(Position *)));
      if (!tmpSpawns) {
        Logger::log(Logger::Error, "Error al reservar memoria. LevelLoader::loadSpawns");
        *spawnCount = 0;
        return NULL;
      }
      Position *pos = new Position((x * 32) + dx + i * (WIDTH / 32), HEIGHT - (1 + y) * 32 - dy);
      tmpSpawns[*spawnCount] = pos;
      (*spawnCount)++;
    }

  }

  return tmpSpawns;
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