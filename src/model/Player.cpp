

#include <SDL.h>
#include "Player.h"
#include "Position.h"
enum kindOfAnimation { left, right};

Player::Player(Position* pos) : Entity(pos) {
    this->pos = pos;
}
void Player::update() {

    if (!isGrounded && pos->getY() > 200) {
        pos->setY(200);
        velY = 0;
        isGrounded = true;
    }
    pos->add(velX, velY);
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

