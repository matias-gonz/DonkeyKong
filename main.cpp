#include "src/model/Game.h"
Game* game = NULL;

int main( int argc, char* args[] ) {

    game = new Game();
    game->init("Donkey Kong",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,576,false);

    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
  
    return 0;
}

