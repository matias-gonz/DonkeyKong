#include <iostream>
#include <SDL2/SDL_events.h>
#include <chrono>
#include "src/model/Game.h"
#include "src/model/Logger.h"
#include "src/view/ViewManager.h"
#include "src/controller/GameController.h"
#include "src/controller/Configuration.h"

int main(int argc, char *args[]) {
    Configuration *configuration = new Configuration();
    Logger::startLogger(configuration);
    Game *game = new Game(configuration);
    game->start();

    GameController *gameController = new GameController(game);
    ViewManager *viewManager = new ViewManager(game, configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                               1024, 576, false);

    while (game->isRunning()) {
        auto startTime = std::chrono::system_clock::now();
        gameController->handleEvents();
        gameController->update();
        viewManager->renderWindow();
        auto endTime = std::chrono::system_clock::now();
        //printf("%d\n",(endTime - startTime).count());

        //sleep((endTime - startTime).count() + 0.06);

    }

    delete game;

    return 0;
}