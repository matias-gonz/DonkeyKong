#include "mainClient.h"
#include "Client.h"


int mainClient(char *IP, char *port) {
    //pantalla login
    //manda msg al server y lo autentica

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


    while (client->isRunning()) {
        //hacer un thread de sends(tendra que ser un while true)
        client->setSended(false);
        client->send();
        //hacer un thread de receives
        client->receive();
        client->render();
    }
}
    return 0;

}