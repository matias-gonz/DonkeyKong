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
                Logger::log(Logger::Debug,"Personaje 1 se movio para la izquierda");
                break;
            case SDLK_RIGHT:
                player->addRightVel();
                Logger::log(Logger::Debug,"Personaje 1 se movio para la derecha");
                break;
            case SDLK_UP:
                player->jumpUp();
                Logger::log(Logger::Debug,"Personaje 1 salto");
                break;
            case SDLK_l:
                this->game->switchLevel();
                Logger::log(Logger::Info,"Se paso al siguiente nivel");
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
    this->game->update();
}