

#include <SDL.h>
#include "Player.h"
#include "Position.h"

Player::Player(){
    velX = 0;
    velY = 0;
    isGrounded = true;
}


void Player::update() {
    if(pos.getY() >= 200){
        pos.setY(200);
        velY = 0;
    }
    pos.add(velX,velY);
}

void Player::addLeftVel(){
    if(velX != 0){
        return;
    }
    velX -= VEL;
}
void Player::addRightVel(){
    if(velX != 0){
        return;
    }
    velX += VEL;
}
void Player::jumpUp() {
    if (!isGrounded){
        return;
    }
    velY += 10*VEL;
    isGrounded = false;
}

void Player::resetVel(){
    this->velX = 0;
}

double Player::getXPosition(){
    return pos.getX();
}


double Player::getYPosition(){
    return pos.getY();
}