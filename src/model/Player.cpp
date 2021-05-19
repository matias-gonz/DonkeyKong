

#include <SDL.h>
#include "Player.h"
#include "Position.h"
enum kindOfAnimation { left = -1, right = 1};

Player::Player(Position* pos) : Entity(pos) {
    this->pos = pos;
    this->isGrounded = true;
    this->counter = 0;
}
void Player::update() {

    if (!isGrounded && pos->getY() > 525) {
        pos->setY(525);
        velY = 0;
        isGrounded = true;
    }

    pos->add(velX, velY);
    if(pos->getX() < 0 or pos->getX()> 1024-17){
        pos->add(-velX,0);
    }//WIDTH - texW
    distance += abs(velX);
    if (distance > 70){ distance = 0;}

    if (counter == 2){
        if (!isGrounded) { velY += 1; }
        counter = 0;
        return;
    }
    counter++;

}

void Player::addLeftVel() {

    if (velX < 0){return;}
    if (velX > 0){ distance = 0;}
    velX -= VEL;
    direction = left;
}

void Player::addRightVel() {

    if (velX > 0){return;}
    if (velX < 0){ distance = 0;}
    velX += VEL;
    direction = right;
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

