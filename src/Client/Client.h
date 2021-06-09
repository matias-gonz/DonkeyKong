#ifndef TALLER_PROG_I_2021_1C_KIWI_CLIENT_H
#define TALLER_PROG_I_2021_1C_KIWI_CLIENT_H

#include "../model/Logger.h"
#include "../Socket/ClientSocket.h"
#include "../Constants.h"
#include "../model/Game.h"
#include "../model/Logger.h"
#include "../view/ViewManager.h"
#include "../controller/GameController.h"
#include "../controller/Configuration.h"


class Client {

public:

    Client(char *port, char *IP);

    void send();

    void receive();

private:

    ViewManager *viewManager;
    ClientSocket *socket;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_CLIENT_H
