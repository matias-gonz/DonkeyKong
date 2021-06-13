#ifndef TALLER_PROG_I_2021_1C_KIWI_CLIENT_H
#define TALLER_PROG_I_2021_1C_KIWI_CLIENT_H

#include "ClientSocket.h"

#include "../Constants.h"
#include "../model/Game.h"
#include "../model/Logger.h"
#include "../view/ViewManager.h"
#include "../controller/GameController.h"
#include "../controller/Configuration.h"
#include "../controller/LoginController.h"


class Client {

public:

  Client(char *port, char *IP);

  bool gameHasStarted();

  void checkValid();

private:

  bool quit, gameStarted;
  LoginController *loginController;
  ViewManager *viewManager;

};


#endif //TALLER_PROG_I_2021_1C_KIWI_CLIENT_H
