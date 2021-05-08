

#include <SDL.h>
#include "Player.h"
#include "Position.h"
enum kindOfAnimation { left, right};

const int LEFTSTARTW = 0;
const int LEFTSTARTH = 30;
const int RIGHTSTARTW = 0;
const int RIGHTSTARTH = 52;
const int texW = 17;
const int texH = 30;

Player::Player(SDL_Texture *playerTexture) {
    this->playerTexture = playerTexture;
    velX = 0;
    velY = 0;
    isGrounded = true;
    this->animator = Animator(playerTexture, LEFTSTARTW, LEFTSTARTH, RIGHTSTARTW, RIGHTSTARTH,texW,texH);
    kindOfAnimation = right;
}


void Player::update() {

    if (!isGrounded && pos.getY() > 200) {
        pos.setY(200);
        velY = 0;
        isGrounded = true;
    }
    pos.add(velX, velY);

    if (!isGrounded) { velY += 1; }
}

void Player::addLeftVel() {
    if (velX != 0) {
        return;
    }
    velX -= VEL;
    kindOfAnimation = left;
}

void Player::addRightVel() {
    if (velX != 0) {
        return;
    }
    velX += VEL;
    kindOfAnimation = right;
}

void Player::jumpUp() {
    if (!isGrounded) {
        return;
    }
    velY -= 2*VEL;
    isGrounded = false;
}

void Player::resetVel() {
    this->velX = 0;
}

void Player::show(SDL_Renderer *renderer) {
    this->animator.draw(renderer,this->kindOfAnimation,&pos);
    //SDL_Rect dstrect = {static_cast<int>(pos.getX()), static_cast<int>(pos.getY()), 25, 50};
    //SDL_RenderCopy(renderer, this->playerTexture, NULL, &dstrect);
}

