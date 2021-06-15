#include <SDL.h>
#include "Player.h"
#include "Position.h"
#include "../Constants.h"
PlayerTexture plyrTex;

Player::Player(Position* pos) : Entity(pos) {
    this->pos = pos;
    this->initialPos = new Position(pos->getX(),pos->getY());
    this->isGrounded = true;
    this->isClimbing = false;
    this->canClimb = false;
    this->counter = 0;
    this->gravity = 1;
    this->distance = 0;
    this->direction = left;
    this->active =true;
}
void Player::update() {

    if(this->isClimbing){
        this->resetVelX();
        this->gravity = 0;
        distance -= 5*velY;
    }else{
        if(direction == up){
            distance = 0;
            direction = left;
        }
        this->gravity = 1;
    }

    pos->add(velX, velY);

    if(pos->getX() < 0 or pos->getX()> WIDTH-plyrTex.walkWidth){
        pos->add(-velX,0);
    }//WIDTH - texW

    if(isGrounded){distance += abs(velX);}
    if (distance > 70){ distance = 0;}


    if (counter == 2){
        if(velY == 5){velY = 4;return;} //(Velocidad terminal) Este 5 es por la las colisiones (1/4 de la altura de la plataforma)
        velY += this->gravity;
        counter = 0;
        return;
    }
    counter++;

}

void Player::addLeftVel() {

    if (direction == right){
        distance = 0;
        direction = left;
    }
    velX = -VEL;
}

void Player::addRightVel() {

    if (direction == left){
        distance = 0;
        direction = right;
    }
    velX = VEL;
}

void Player::jumpUp() {
    if (!isGrounded) {
        return;
    }
    velY -= 2*VEL;
    isGrounded = false;
    isClimbing = false;
}

void Player::resetVelX() {
    this->velX = 0;
}

SDL_Rect Player::getRectangle() {
    return SDL_Rect({this->pos->getX(),this->pos->getY(),plyrTex.walkWidth, plyrTex.walkHeight});
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
    return ((this->pos->getX() > pPosition->getX() and this->pos->getX() < pPosition->getX() + 170)\
        and (this->pos->getY() < 154));
}

void Player::startClimbing(int vel) {
    if(!this->canClimb) return;
    this->velY = vel;
    this->isClimbing = true;
    this->isGrounded = true;
    this->direction = up;

}

void Player::setCanClimb(bool canClimb) {
    if(!canClimb){
        this->isClimbing = false;
    }
    this->canClimb = canClimb;
}

void Player::stoppedPlaying() {
    this->active = false;
}

bool Player::isPlaying() {
    return this->active;
}
