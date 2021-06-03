#include "mainClient.h"
#include "Client.h"


int mainClient(char* IP, char* port){
  Client* client = new Client(port, IP);

  Configuration *configuration = new Configuration();
  Logger::startLogger(configuration);

  /* Game *game = new Game(configuration);
  game->start();

  GameController *gameController = new GameController(game);
  ViewManager *viewManager = new ViewManager(game, configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

  while (game->isRunning()) {
    gameController->handleEvents();
    gameController->update();
    viewManager->renderWindow();
  } */

  return 0;

}