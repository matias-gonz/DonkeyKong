#include "Client.h"

#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(char *port, char *IP) {
  Configuration *configuration = new Configuration();
  //Logger::startLogger(configuration);

  /* Game *game = new Game(configuration);
  game->start();

  GameController *gameController = new GameController(game);


  while (game->isRunning()) {
    gameController->handleEvents();
    gameController->update();
    viewManager->renderWindow();
  } */

  this->viewManager = new ViewManager(configuration,"Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                               SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

  this->socket = new ClientSocket(port, IP);

  // delete game;
}

void Client::receive() {
    this->socket->receive(NULL);
}

void Client::send() {
    this->socket->send((void*)"hola\n");
}
