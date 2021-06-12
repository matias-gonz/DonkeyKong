#ifndef TALLER_PROG_I_2021_1C_KIWI_CLIENT_H
#define TALLER_PROG_I_2021_1C_KIWI_CLIENT_H

#include "../model/Logger.h"
#include "../Socket/ClientSocket.h"
#include "../Constants.h"
#include "../model/Logger.h"
#include "../view/ViewManager.h"
#include "../controller/Configuration.h"


class Client {

public:

    Client(char *port, char *IP);

    void send();

    void receive();
    bool isRunning();

    void render();

    void setSended(bool b);

private:
    Positions playerPositions;
    ViewManager *viewManager;

    ClientSocket *socket;
    Configuration *configuration;
    bool eventIsValid(SDL_Event event);

    bool running;
    bool sended;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_CLIENT_H
