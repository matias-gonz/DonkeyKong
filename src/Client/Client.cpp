#include "Client.h"

#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(char *port, char *IP) {
  Configuration *configuration = new Configuration();
  Logger::startLogger("log.txt", configuration);

  Game *game = new Game(configuration);
  game->start();

  GameController *gameController = new GameController(game);
  ViewManager *viewManager = new ViewManager(game, configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             1024, 576, false);

  while (game->isRunning()) {
    gameController->handleEvents();
    gameController->update();
    viewManager->renderWindow();
  }

  ClientSocket *new_socket = new ClientSocket(port, IP);

  delete game;
}
