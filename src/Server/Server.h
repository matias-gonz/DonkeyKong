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

    void update();

    void start();

    bool isFull();

    void addNewConnection();

private:
    ServerSocket *socket;
    Configuration *configuration;
    Game *game;
    GameController *gameController;
    Positions plyrPos;
    void *updateThread(void *socket);
    cola_t *eventQueue;
    void broadcast();

    char *port;
    char *ip;
    int clientCount;
    int clientMax;
    int *sockets;
    pthread_mutex_t mutex;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_SERVER_H
