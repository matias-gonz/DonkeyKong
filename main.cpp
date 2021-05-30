#include <iostream>
#include <SDL2/SDL_events.h>
#include "src/model/Game.h"
#include "src/model/Logger.h"
#include "src/view/ViewManager.h"
#include "src/controller/GameController.h"
#include "src/controller/Configuration.h"
#include "src/model/TimeManager.h"




int main(int argc, char *args[]) {
    Configuration *configuration = new Configuration();
    Logger::startLogger(configuration);
    TimeManager *timeManager = new TimeManager();
    Game *game = new Game(configuration);
    game->start();

    GameController *gameController = new GameController(game);
    ViewManager *viewManager = new ViewManager(game, configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                               1024, 576, false);

    while (game->isRunning()) {
        timeManager->setStartTime();
        gameController->handleEvents();
        gameController->update();
        viewManager->renderWindow();
        timeManager->setEndTime();
        timeManager->sleep();


    }

    delete game;

    return 0;
}