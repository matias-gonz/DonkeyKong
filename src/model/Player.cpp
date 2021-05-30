

#include <SDL.h>
#include "Player.h"
#include "Position.h"
enum kindOfAnimation { left = -1, right = 1};

Player::Player(Position* pos) : Entity(pos) {
    this->pos = pos;
    this->initialPos = new Position(pos->getX(),pos->getY());
    this->isGrounded = true;
    this->counter = 0;
}
void Player::update() {

    /*
    if (!isGrounded && pos->getY() > 525) {
        pos->setY(525);
        velY = 0;
        isGrounded = true;
    }
     */
    pos->add(velX, velY);
    if(pos->getX() < 0 or pos->getX()> 1024-17){
        pos->add(-velX,0);
    }//WIDTH - texW
    distance += abs(velX);
    if (distance > 70){ distance = 0;}


    if (counter == 2){
        if(velY == 5){velY = 4;return;} //(Velocidad terminal) Este 5 es por la las colisiones (1/4 de la altura de la plataforma)
        velY += 1;
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

void Player::resetVelX() {
    this->velX = 0;
}

SDL_Rect Player::getRectangle() {
    return SDL_Rect({this->pos->getX(),this->pos->getY(),34, 30});
}

void Player::moveUp(int dy) {
    this->pos->add(0,-dy);
}

void Player::setGrounded() {
    this->isGrounded = true;

}

void Player::resetVelY() {
    this->velY = 0;
}


int Player::getVelY() {
    return this->velY;
}

void Player::resetPos() {
   *this->pos = *this->initialPos;
}

Player::~Player(){
    delete this->initialPos;
}

bool Player::isIn(Position *pPosition) {
    if((this->pos->getX() > pPosition->getX() and this->pos->getX() < pPosition->getX() + 170)\
        and (this->pos->getY() < 154)){
        return true;
    }
    return false;
}
