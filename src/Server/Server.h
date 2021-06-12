#ifndef TALLER_PROG_I_2021_1C_KIWI_SERVER_H
#define TALLER_PROG_I_2021_1C_KIWI_SERVER_H

#include <SDL2/SDL_events.h>
#include <netinet/in.h>
#include <pthread.h>

#include "../model/Game.h"
#include "../model/Logger.h"
#include "../Constants.h"
#include "../view/ViewManager.h"
#include "../controller/GameController.h"
#include "../controller/Configuration.h"
#include "../Socket/ServerSocket.h"
#include "../Queue.h"

class Server {

public:

    Server(char *port, char *IP);

    bool isRunning();

    static void update();

private:
    ServerSocket *socket;

    static ServerSocket *sockets[4];

    Configuration *configuration;
    static Game *game;
    static GameController *gameController;

    static Positions plyrPos;

    static void *updateThread(void *socket);

    static cola_t *eventQueue;

    static void broadcast();
};

#endif //TALLER_PROG_I_2021_1C_KIWI_SERVER_H
