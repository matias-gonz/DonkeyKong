

#include <SDL.h>
#include "Player.h"
#include "Position.h"

Player::Player(SDL_Texture* playerTexture){
    this->playerTexture = playerTexture;
    velX = 0;
    velY = 0;
    isGrounded = true;
}


void Player::update() {
    pos.add(velX,velY);
}

void Player::addLeftVel(){
    velX -= VEL;
}
void Player::addRightVel(){
    velX += VEL;
}
void Player::jumpUp() {
    if (isGrounded){
        return;
    }
}

void Player::show(SDL_Renderer* renderer) {
    SDL_Rect dstrect = {static_cast<int>(pos.getX()), static_cast<int>(pos.getY()), 50, 100 };
    SDL_RenderCopy(renderer,this->playerTexture,NULL,&dstrect);
}

