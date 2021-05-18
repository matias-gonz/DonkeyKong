#ifndef TALLER_PROG_I_2021_1C_KIWI_GAMECONTROLLER_H
#define TALLER_PROG_I_2021_1C_KIWI_GAMECONTROLLER_H

#include "SDL2/SDL.h"
#include "../model/Game.h"
#include "../model/Logger.h"

class GameController {
public:
    GameController(Game* game);

    void handleEvents();

    void update();

private:
    Game* game;

    Player *player;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_GAMECONTROLLER_H
