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
#include "../controller/LoginController.h"
#include "credentials.h"

class Client {

public:

  Client(char *port, char *IP);

  void send();

  void sendString(char *string);

  void receive();

  bool isRunning();

  void render();

  void setSended(bool b);

  bool checkCredentials();

  bool gameHasStarted();

  void checkValid();

  void goToLobby();

  void checkUsernameBoxes();

  void startPlaying();

  char *rcvString();

  bool isInLobby();

private:
  Positions positions;
  ViewManager *viewManagerLogin, *viewManagerGame, *viewManagerLobby;

  bool quit, gameStarted, _isInLobby;
  LoginController *loginController;

  ClientSocket *socket;
  Configuration *configuration;

  bool eventIsValid(SDL_Event event);

  bool running;
  bool sended;
  bool userBoxes[20];
};


#endif //TALLER_PROG_I_2021_1C_KIWI_CLIENT_H
