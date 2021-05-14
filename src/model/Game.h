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

    void update();

    void quit();

    bool isRunning();

    Level *getLevel();

    Player *getPlayer();

    void loadLevel(int i);

private:
    Player *player = NULL;
    bool running;
    Level *level;

};


#endif //TALLER_PROG_I_2021_1C_KIWI_GAME_H
