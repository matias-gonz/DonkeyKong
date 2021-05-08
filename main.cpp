#include "src/model/Game.h"
#include "src/view/TextureManager.h"

Game *game = NULL;

void loadImages();

SDL_Texture *playerTexture;


int main(int argc, char *args[]) {

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

        //SDL_Delay(1000/50);
    }
    game->clean();

    return 0;
}

void loadImages() {
    playerTexture = TextureManager::LoadTexture("resources/sprites/sans_walk.png");
}

