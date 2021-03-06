#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVEL_H

#include <SDL2/SDL_image.h>

#include "Platform.h"
#include "Ladder.h"
#include "Fire.h"
#include "Barrel.h"
#include "LevelLoader.h"

#include "../view/TextureManager.h"
#include "../controller/Configuration.h"
#include "player/Player.h"
#include "EnemyFire.h"
#include "Hammer.h"

class Level {

public:
    Level();

    ~Level();

    void loadLevel(int levelnum, Configuration* configuration);

    void update();

    int getLadderCount();

    Ladder *getLadder(int i);

    int getPlatformCount();

    Platform *getPlatform(int i);

    int getFireCount();

    Fire *getFire(int i);

    int getBarrelCount();
    Barrel *getBarrel(int i);

    Position **getSpawns();

    int getSpawnCount();

    int getCurrentLevel();

    void resolveCollisions(Player **players, int playerCount, EnemyFire **fires, int fireCount, Hammer ***hammers, int *hammerCount);

    bool playerWon(Player *pPlayer);

private:

    Platform **platforms;
    int platformCount;

    Ladder **ladders;
    int ladderCount;

    Fire **fires;
    int fireCount;

    Position **spawns;
    int spawnCount;

    LevelLoader *loader;
    Barrel **barrels;
    int barrelCount;

    void reset();

    void freePlaforms();

    void freeLadders();

    void freeFires();

    void freeSpawns();

    int currentLevel;

    void freeBarrels();

    Position* winningPosition = new Position(450,80);
    int counter;

    void spawnBarrel();

    void burnBarrel(int i);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
