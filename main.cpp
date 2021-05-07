
#include "src/model/Game.h"
#include "src/view/TextureLoader.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include<SDL2/SDL_events.h>
#include "src/view/ltexture.h"
#include "src/model/barrel.h"
#include "src/view/viewManager.h"

Game* game = NULL;

void loadImages();

SDL_Texture* playerTexture;

ViewManager *viewManager = new ViewManager();
void renderBarrel();

int main(int argc, char* args[] ) {

    game = new Game();
    game->init("Donkey Kong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 576, false);

    loadImages();
    if (playerTexture == NULL) {
        printf("%s", SDL_GetError());
    }

    Player player = Player(playerTexture);
    game->player = &player;

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();

    }
    game->clean();

    renderBarrel();

    return 0;

}

void loadImages() {
    playerTexture = TextureLoader::loadTexture("resources/sprites/sans_left.png");
}



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
