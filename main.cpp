
#include <iostream>
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL_events.h>

#include "src/model/Game.h"
#include "src/view/ltexture.h"
#include "src/view/TextureManager.h"
#include "src/view/viewManager.h"
#include "src/controller/GameController.h"
#include "src/controller/Configuration.h"

Game* game = NULL;

int main(int argc, char* args[] ) {
    Game* game = new Game();
    game->start();

    GameController* gameController = new GameController(game);
    ViewManager* viewManager = new ViewManager(game);

    while (game->isRunning()) {
        gameController->handleEvents();
        gameController->update();
        viewManager->renderWindow();
    }


    Configuration* configuration = new Configuration();
    std::cout << to_string(configuration->log.at("level")) + "\n";

    return 0;
}

void Game::render() {
    SDL_RenderClear(renderer);

    this->level->drawLevel();

    SDL_RenderPresent(renderer);
}

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
