#include "GameController.h"

GameController::GameController(Game* aGame){
    this->game = aGame;
}
void GameController::handleEvents(SDL_Event event, int i) {
    this->player = this->game->getPlayer(i);
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT or event.key.keysym.sym == SDLK_a) {
            player->resetVelX();
            player->addLeftVel();
            Logger::log(Logger::Debug, "presiono izquierda",i);
        } else if (event.key.keysym.sym == SDLK_RIGHT or event.key.keysym.sym == SDLK_d) {
            player->resetVelX();
            player->addRightVel();
            Logger::log(Logger::Debug, "presiono derecha",i);
        } else if (event.key.keysym.sym == SDLK_UP or event.key.keysym.sym == SDLK_w) {
            player->startClimbing(-1);
            Logger::log(Logger::Debug, "presiono arriba",i);
        } else if (event.key.keysym.sym == SDLK_DOWN or event.key.keysym.sym == SDLK_s) {
            player->startClimbing(1);
            Logger::log(Logger::Debug, "presiono abajo",i);
        } else if (event.key.keysym.sym == SDLK_SPACE) {
            player->jumpUp();
            printf("%s\n",player->getUsername());
            Logger::log(Logger::Debug, "presiono salto",i);
        } else if (event.key.keysym.sym == SDLK_l) {
            this->game->switchLevel();
            Logger::log(Logger::Debug, "presiono paso de nivel",i);
        } else if (event.key.keysym.sym == SDLK_g) {
            this->game->switchGod(i);
            Logger::log(Logger::Debug, "Switched God Mode",i);
        }
    }
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_LEFT or event.key.keysym.sym == SDLK_a) {
            player->resetVelX();
            Logger::log(Logger::Debug, "se mueve a la izquierda",i);
        }else if (event.key.keysym.sym == SDLK_RIGHT or event.key.keysym.sym == SDLK_d) {
            player->resetVelX();
            Logger::log(Logger::Debug, "se mueve a la derecha",i);
        }else if (event.key.keysym.sym == SDLK_UP or event.key.keysym.sym == SDLK_w) {
            player->resetVelY();
            Logger::log(Logger::Debug, "intenta escalar hacia arriba",i);
        }else if (event.key.keysym.sym == SDLK_DOWN or event.key.keysym.sym == SDLK_s) {
            player->resetVelY();
            Logger::log(Logger::Debug, "intenta escalar hacia abajo",i);
        }
    }
    if (event.type == SDL_QUIT){
        player->stoppedPlaying();
        game->updateStatus();
        Logger::log(Logger::Info, "dejo de jugar",i);
    }
}

void GameController::update() {
    this->game->update();
}