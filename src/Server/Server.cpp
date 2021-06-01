#include "Server.h"

Server::Server(char *port, char *IP) {

  Configuration *configuration = new Configuration();
  Logger::startLogger(configuration);

  /* GameController *gameController = new GameController(game);
  ViewManager *viewManager = new ViewManager(game, configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

  while (game->isRunning()) {
    gameController->handleEvents();
    gameController->update();
    viewManager->renderWindow();
  } */

  ServerSocket *new_socket = new ServerSocket(port, IP);

  // delete game;
}
