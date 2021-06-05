#include "Client.h"

#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(char *port, char *IP) {

  ClientSocket *new_socket = new ClientSocket(port, IP);

  if(new_socket->isConnected()){
    ViewManager* viewManager = new ViewManager("Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                               SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT);
    viewManager->renderLoginWindow();
  }
  // delete game;
}
