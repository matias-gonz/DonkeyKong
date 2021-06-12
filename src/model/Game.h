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

    Player *getPlayer(int i);

    void loadLevel(int i);

    Boss* getBoss();
    Princess* getPrincess();
    EnemyFire **getEnemyFires();

    int getEnemyFireCount();

    void switchLevel();

    void addPlayer();

private:
    Player *players[4] = {NULL,NULL,NULL,NULL};
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
};


#endif //TALLER_PROG_I_2021_1C_KIWI_GAME_H
