#ifndef TALLER_PROG_I_2021_1C_KIWI_SERVER_H
#define TALLER_PROG_I_2021_1C_KIWI_SERVER_H

#include <SDL2/SDL_events.h>
#include <netinet/in.h>

#include "../model/Game.h"
#include "../model/Logger.h"
#include "../Constants.h"
#include "../view/ViewManager.h"
#include "../controller/GameController.h"
#include "../controller/Configuration.h"
#include "../Socket/ServerSocket.h"


class Server {

public:

  Server(char *port, char *IP);

    bool isRunning();

    void receive();

    void update();

    void broadcast();

private:
    ServerSocket *socket;
    SDL_Event plyrEvent;
    Configuration *configuration;
    Game *game;
    GameController *gameController;
    Positions plyrPos;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_SERVER_H
