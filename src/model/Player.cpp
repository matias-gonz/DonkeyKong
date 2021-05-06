

#include <SDL.h>
#include "Player.h"
#include "Position.h"

Player::Player(SDL_Texture *playerTexture) {
    this->playerTexture = playerTexture;
    velX = 0;
    velY = 0;
    isGrounded = true;
}


void Player::update() {
    if (!isGrounded && pos.getY() > 200) {
        pos.setY(200);
        velY = 0;
        isGrounded = true;
    }
    pos.add(velX, velY);

}

void Player::addLeftVel() {
    if (velX != 0) {
        return;
    }
    velX -= VEL;
}

void Player::addRightVel() {
    if (velX != 0) {
        return;
    }
    velX += VEL;
}

void Player::jumpUp() {
    if (!isGrounded) {
        return;
    }
    velY -= VEL;
    isGrounded = false;
}

void Player::resetVel() {
    this->velX = 0;
}

void Player::show(SDL_Renderer *renderer) {
    if (!isGrounded) { velY += 1; }
    SDL_Rect dstrect = {static_cast<int>(pos.getX()), static_cast<int>(pos.getY()), 25, 50};
    SDL_RenderCopy(renderer, this->playerTexture, NULL, &dstrect);
}

