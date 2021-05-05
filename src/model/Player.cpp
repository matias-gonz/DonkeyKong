

#include <SDL.h>
#include "Player.h"
#include "Position.h"

Player::Player(SDL_Texture* playerTexture){
    this->playerTexture = playerTexture;
    velX = 0;
    velY = 0;
    isGrounded = true;
}


void Player::handleEvent(SDL_Event &e){
    switch( e.key.keysym.sym )
    {
        //case SDLK_UP: aca tiene que estar lo que hace cuando salta
        //case SDLK_DOWN: aca va a estar lo que haga cuando se tenga que agachar o bajar
        case SDLK_LEFT: velX -= VEL; break;
        case SDLK_RIGHT: velX += VEL; break;
    }
}
void Player::move() {
    pos.add(velX,velY);
}


void Player::jumpUp() {
    if (isGrounded){
        return;
    }
}

void Player::show(SDL_Renderer* renderer) {
    SDL_Rect dstrect = {static_cast<int>(pos.getX()), static_cast<int>(pos.getY()), 100, 200 };
    SDL_RenderCopy(renderer,this->playerTexture,NULL,&dstrect);
}

