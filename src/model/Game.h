#ifndef TALLER_PROG_I_2021_1C_KIWI_GAME_H
#define TALLER_PROG_I_2021_1C_KIWI_GAME_H
#include "SDL2/SDL.h"
#include "Player.h"
#include "Level.h"
#include "EnemyFire.h"
#include "Logger.h"
class Game {

public:
    Game();
    ~Game();

    void start();
    void update();

    void quit();

    bool isRunning();

    Level *getLevel();

    Player *getPlayer();

    void loadLevel(int i);

    EnemyFire **getEnemyFires();

    int getEnemyFireCount();

    void switchLevel();

private:
    Player *player = NULL;
    EnemyFire** enemyFires = NULL;
    int enemyFireCount = 0;
    bool running;
    Level *level;

    void spawnEnemies(Position **spawns, int spawnCount);

    void resetEnemies();

    int currentLevel;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_GAME_H
