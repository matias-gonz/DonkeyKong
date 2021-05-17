#ifndef TALLER_PROG_I_2021_1C_KIWI_GAME_H
#define TALLER_PROG_I_2021_1C_KIWI_GAME_H
#include "SDL2/SDL.h"
#include "Player.h"
#include "Level.h"
#include "EnemyFire.h"
#include "Boss.h"

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

    EnemyFire* getEnemyFire();
    Boss* getBoss();
private:
    Player *player = NULL;
    EnemyFire* enemyFire = NULL;
    Boss*  boss = NULL;
    bool running;
    Level *level;

};


#endif //TALLER_PROG_I_2021_1C_KIWI_GAME_H
