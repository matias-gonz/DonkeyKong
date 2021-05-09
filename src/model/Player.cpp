

#include <SDL.h>
#include "Player.h"
#include "Position.h"
enum kindOfAnimation { left, right};

const int LEFTSTARTW = 0;
const int LEFTSTARTH = 30;
const int RIGHTSTARTW = 0;
const int RIGHTSTARTH = 52;
const int SEPARATIONW = 5;
const int texW = 17;
const int texH = 30;

Player::Player(){
    velX = 0;
    velY = 0;
    isGrounded = true;
    this->animator = Animator(playerTexture, LEFTSTARTW, LEFTSTARTH, RIGHTSTARTW, RIGHTSTARTH,texW,texH,SEPARATIONW);
    kindOfAnimation = right;
    distance = 0;
}


void Player::update() {

    if (!isGrounded && pos.getY() > 200) {
        pos.setY(200);
        velY = 0;
        isGrounded = true;
    }
    pos.add(velX, velY);
    distance += abs(velX);
    if (distance > 70){ distance = 0;}

    if (!isGrounded) { velY += 1; }
}

void Player::addLeftVel() {

    if (velX < 0){return;}
    if (velX > 0){ distance = 0;}
    velX -= VEL;
    kindOfAnimation = left;
}

void Player::addRightVel() {

    if (velX > 0){return;}
    if (velX < 0){ distance = 0;}
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

double Player::getXPosition(){
    return pos.getX();
}


double Player::getYPosition(){
    return pos.getY();
}