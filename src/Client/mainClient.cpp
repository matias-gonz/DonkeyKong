#include "mainClient.h"
#include "Client.h"


mainClient::mainClient(char *IP, char *port) {
  Client *client = new Client(port, IP);

  //TODO change inside if
  if (client->gameHasStarted()) {
    Configuration *configuration = new Configuration();
    Logger::startLogger(configuration);
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
    delete game;
  }
}
