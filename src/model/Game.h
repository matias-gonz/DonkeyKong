#ifndef TALLER_PROG_I_2021_1C_KIWI_GAME_H
#define TALLER_PROG_I_2021_1C_KIWI_GAME_H

#include "Player.h"
#include "Level.h"
#include "EnemyFire.h"
#include "Boss.h"
#include "Princess.h"
#include "../controller/Configuration.h"
#include "Logger.h"

class Game {

public:
    Game(Configuration* configuration);

    ~Game();

    void start();

    void update();

    void quit();

    bool isRunning();

    Level *getLevel();

    Player *getPlayer();

    void loadLevel(int i);

    Boss* getBoss();
    Princess* getPrincess();
    EnemyFire **getEnemyFires();

    int getEnemyFireCount();

    void switchLevel();

    void addPlayer();

    void getPlatforms(PlatformContainer *platforms, int *count);

    void getLadders(LadderContainer *ladders, int *count);

    void getFires(FireContainer *fires, int *count);

    void getEnemyFiresPos(EntityContainer *enemyFires, int *count);

    void getPLayerInfo(EntityContainer* playerInfo);

    void getBossInfo(EntityContainer *bossInfo);

    void getPrincessInfo(EntityContainer *princessInfo);

private:
    Player *player;
    EnemyFire** enemyFires = NULL;
    int enemyFireCount = 0;
    Boss*  boss = NULL;
    Princess* princess = NULL;
    bool running;
    Level *level;
    Configuration* configuration;

    void spawnEnemies(Position **spawns, int spawnCount, int probability);

    void resetEnemies();

    int currentLevel;

    void resolveCollisions();

    void getEntityInfo(EntityContainer *entityInfo, Entity *entity);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_GAME_H
