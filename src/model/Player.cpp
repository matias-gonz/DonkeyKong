

#include <SDL.h>
#include "Player.h"
#include "Position.h"

Player::Player(double xInit, double yInit): pos(xInit, yInit){
    pos = Position(xInit, yInit);
    velX = 0;
    velY = 0;
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


