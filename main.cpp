#include <iostream>
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL_events.h>

#include "src/model/Game.h"

#include "src/model/Logger.h"
#include "src/view/TextureManager.h"
#include "src/view/ViewManager.h"
#include "src/controller/GameController.h"
#include "src/controller/Configuration.h"

int main(int argc, char *args[]) {
    Logger::startLogger("log.txt");
    Game *game = new Game();
    game->start();

    Configuration *configuration = new Configuration();
    GameController *gameController = new GameController(game);
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
/*
void Game::render() {
    SDL_RenderClear(renderer);

    this->level->drawLevel();

    SDL_RenderPresent(renderer);
}
*/

/*
void renderBarrel() {
  //Start up SDL and create window
  if (!viewManager->successfulInitialitization()) {
    printf("Failed to initialize!\n");
  } else {
    LTexture* barrelTexture = viewManager->loadTexture("resources/sprites/search.png");
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //The barrel that will be moving around on the screen
    Barrel barrel;
    barrel.setTexture(barrelTexture);

    //While application is running
    while (!quit) {
      //Handle events on queue
      while (SDL_PollEvent(&event) != 0) {
        //User requests quit
        if (event.type == SDL_QUIT) {
          quit = true;
        }
      }

      //Move the barrel
      barrel.move();

      //Clear screen
      SDL_SetRenderDrawColor(viewManager->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(viewManager->getRenderer());

      //Render objects
      barrel.render();

      //Update screen
      SDL_RenderPresent(viewManager->getRenderer());
    }
  }

  //Free resources and close SDL
  viewManager->close();
}
*/
