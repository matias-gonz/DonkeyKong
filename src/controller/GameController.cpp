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
        if(event.key.keysym.sym == SDLK_LEFT or event.key.keysym.sym == SDLK_a ){
            player->addLeftVel();
        }
        else if(event.key.keysym.sym == SDLK_RIGHT or event.key.keysym.sym == SDLK_d){
            player->addRightVel();
        }
        else if(event.key.keysym.sym == SDLK_SPACE){
            Logger::log(Logger::Debug,"Personaje 1 salto");
            player->jumpUp();
        }
        else if(event.key.keysym.sym == SDLK_l){
            Logger::log(Logger::Info,"Se switchea nivel");
            this->game->switchLevel();
        }
    }
    if (event.type == SDL_KEYUP) {
        if(event.key.keysym.sym == SDLK_LEFT or event.key.keysym.sym == SDLK_a ){
            player->resetVel();
            Logger::log(Logger::Info,"Se mueve a la izquierda");
        }
        else if(event.key.keysym.sym == SDLK_RIGHT or event.key.keysym.sym == SDLK_d){
            player->resetVel();
            Logger::log(Logger::Info,"Se mueve a la derecha");
        }
    }
}

void GameController::update() {
    this->game->update();
}