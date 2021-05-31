#include "GameController.h"

GameController::GameController(Game* aGame){
    this->game = aGame;
    this->player = game->getPlayer();
}
void GameController::handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent( &event ) != 0 ){

        switch (event.type) {
            case SDL_QUIT://añadir evento de minimizar
                game->quit();
                break;
            default:
                break;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_LEFT or event.key.keysym.sym == SDLK_a) {
                player->resetVelX();
                player->addLeftVel();
            } else if (event.key.keysym.sym == SDLK_RIGHT or event.key.keysym.sym == SDLK_d) {
                player->resetVelX();
                player->addRightVel();
            } else if (event.key.keysym.sym == SDLK_UP or event.key.keysym.sym == SDLK_w) {
                player->startClimbing(-1);
            } else if (event.key.keysym.sym == SDLK_DOWN or event.key.keysym.sym == SDLK_s) {
                player->startClimbing(1);
            } else if (event.key.keysym.sym == SDLK_SPACE) {
                Logger::log(Logger::Debug, "Personaje 1 salto");
                player->jumpUp();
            } else if (event.key.keysym.sym == SDLK_l) {
                Logger::log(Logger::Info, "Se switchea nivel");
                this->game->switchLevel();
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_LEFT or event.key.keysym.sym == SDLK_a) {
                player->resetVelX();
                Logger::log(Logger::Info, "Se mueve a la izquierda");
            }if (event.key.keysym.sym == SDLK_RIGHT or event.key.keysym.sym == SDLK_d) {
                player->resetVelX();
                Logger::log(Logger::Info, "Se mueve a la derecha");
            }if (event.key.keysym.sym == SDLK_UP or event.key.keysym.sym == SDLK_w) {
                player->resetVelY();
            }if (event.key.keysym.sym == SDLK_DOWN or event.key.keysym.sym == SDLK_s) {
                player->resetVelY();
            }
        }
    }
}

void GameController::update() {
    this->game->update();
}