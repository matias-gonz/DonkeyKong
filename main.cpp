#include <iostream>
#include <SDL2/SDL_events.h>

#include "src/model/Game.h"
#include "src/model/Logger.h"
#include "src/view/ViewManager.h"
#include "src/controller/GameController.h"
#include "src/controller/Configuration.h"

int main(int argc, char *args[]) {
    Configuration *configuration = new Configuration();
    Logger::startLogger("log.txt");
    Game *game = new Game(configuration);
    game->start();

    GameController *gameController = new GameController(game);
    // pasar json de sprites
    ViewManager *viewManager = new ViewManager(game, configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                               1024, 576, false);

    while (game->isRunning()) {
        gameController->handleEvents();
        gameController->update();
        viewManager->renderWindow();
    }

    delete game;

    return 0;
}