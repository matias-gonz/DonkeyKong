#include "Client.h"

Client::Client(char *port, char *IP) {
  quit = false;
  ClientSocket *new_socket = new ClientSocket(port, IP);

  if(new_socket->isConnected()){
    LoginController* loginController = new LoginController();
    ViewManager* viewManager = new ViewManager("Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                               SDL_WINDOWPOS_CENTERED, LOGIN_WIDTH, LOGIN_HEIGHT);
    while(!quit) {
      loginController->handle(&quit);
      viewManager->renderLoginWindow(&quit);
    }
  }
  // delete game;
}
