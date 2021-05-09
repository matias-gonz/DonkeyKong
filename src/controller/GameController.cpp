#include "GameController.h"

GameController::GameController(Game* aGame){
    this->game = aGame;
    this->player = game->getPlayer();
}
void GameController::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT://añadir evento de minimizar
            game->quit() ;
            break;
        default:
            break;
    }
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                player->addLeftVel();
                break;
            case SDLK_RIGHT:
                player->addRightVel();
                break;
            case SDLK_UP:
                player->jumpUp();
                break;
        }
    }
    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                player->resetVel();
                break;
            case SDLK_RIGHT:
                player->resetVel();
                break;
        }
    }
}

void GameController::update() {
    this->player->update();
}