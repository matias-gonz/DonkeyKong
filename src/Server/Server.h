#ifndef TALLER_PROG_I_2021_1C_KIWI_SERVER_H
#define TALLER_PROG_I_2021_1C_KIWI_SERVER_H

#include <SDL2/SDL_events.h>
#include <netinet/in.h>

#include "../model/Game.h"
#include "../model/Logger.h"
#include "../view/ViewManager.h"
#include "../controller/GameController.h"
#include "../controller/Configuration.h"


class Server
{

public:

  Server(char** port, char** IP);

private:

};

#endif //TALLER_PROG_I_2021_1C_KIWI_SERVER_H
