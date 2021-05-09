
#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_events.h>
#include <iostream>

#include "src/view/TextureManager.h"
#include "src/model/Game.h"
#include "src/view/ltexture.h"
#include "src/model/barrel.h"
#include "src/view/viewManager.h"
#include "src/controller/Configuration.h"

Game* game = NULL;

void loadImages();

SDL_Texture* playerTexture;

ViewManager *viewManager = new ViewManager();
void renderBarrel();

int main(int argc, char* args[] ) {

    /* game = new Game();
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
     */

  //printObjectkeys(jsonConfigRoot, true, 1);
  Configuration* configuration = new Configuration();
  std::cout << to_string(configuration->log.at("level")) + "\n";

  return 0;
}

void loadImages() {
    playerTexture = TextureManager::LoadTexture("resources/sprites/sans_left.png");
}

/* void printObjectkeys(const nlohmann::json& jsonObject, bool recursive, int ident) {
  if (jsonObject.is_object() || jsonObject.is_array()) {
    for (auto &it : jsonObject.items()) {
      std::cout << std::string(ident, ' ')
                << it.key() << " -> "
                << it.value().type_name() << std::endl;
      if (recursive && (it.value().is_object() || it.value().is_array()))
        printObjectkeys(it.value(), recursive, ident + 4);
    }
  }
} */

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
