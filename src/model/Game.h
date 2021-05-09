#ifndef TALLER_PROG_I_2021_1C_KIWI_GAME_H
#define TALLER_PROG_I_2021_1C_KIWI_GAME_H
#include "SDL2/SDL.h"
#include "Player.h"
#include "Level.h"

class Game {

public:
    Game();
    ~Game();

    void start();

    void quit();

    bool isRunning();

    Player* player = NULL;


    Level* getLevel();

    Player* getPlayer();

private:
    bool running;
    Level* level;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_GAME_H
