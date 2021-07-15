#include <SDL.h>
#include "Player.h"
#include "../Position.h"
#include "../../Constants.h"
#include "PlayerState.h"
#include "NormalState.h"
#include "DeadState.h"

PlayerTexture plyrTex;

Player::Player(Position *pos, char *username) : Entity(pos) {
  strcpy(this->username, username);
  this->pos = pos;
  this->initialPos = new Position(pos->getX(), pos->getY());
  this->isGrounded = true;
  this->isClimbing = false;
  this->canClimb = false;
  this->counter = 0;
  this->gravity = 1;
  this->distance = 0;
  this->direction = left;
  this->active = true;
  this->hasWon = false;
  this->canAddPoints = true;
  this->hp = 3;
  this->points = 0;
  this->modeState = new NormalState();
  //this->moveState = new WalkingState();

}

void Player::update() {
  this->modeState->update(this);
  printf("%d %d\n", pos->getX(), pos->getY());
}

void Player::addLeftVel() {

  if (direction == right) {
    distance = 0;
    direction = left;
  }
  velX = -VEL;
}

void Player::addRightVel() {

  if (direction == left) {
    distance = 0;
    direction = right;
  }
  velX = VEL;
}

void Player::jumpUp() {
  if (!isGrounded) {
    return;
  }
  velY -= 2 * VEL;
  isGrounded = false;
  isClimbing = false;
}

void Player::resetVelX() {
  this->velX = 0;
}

SDL_Rect Player::getRectangle() {
  return SDL_Rect({this->pos->getX(), this->pos->getY(), plyrTex.walkWidth, plyrTex.walkHeight});
}

void Player::moveUp(int dy) {
  this->pos->add(0, -dy);
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

Player::~Player() {
  delete this->initialPos;
}

bool Player::isIn(Position *pPosition) {
  return ((this->pos->getX() > pPosition->getX() and this->pos->getX() < pPosition->getX() + 170)\
 and (this->pos->getY() < 154));
}

void Player::startClimbing(int vel) {
  if (!this->canClimb) return;
  this->velY = vel;
  this->isClimbing = true;
  this->isGrounded = true;
  this->direction = up;

}

void Player::setCanClimb(bool canClimb) {
  if (!canClimb) {
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

char *Player::getUsername() {
  return this->username;
}

void Player::startedPlaying() {
  this->active = true;
}

void Player::playerWon() {
  this->hasWon = true;
}

void Player::resetPlayerWon() {
  this->hasWon = false;
}

bool Player::hasplayerWon() {
  return this->hasWon;
}

bool Player::getAddPoints(){
  return this->canAddPoints;
}

void Player::setAddPoints(){
  this->canAddPoints = true;
}

void Player::cantAddPoints(){
  this->canAddPoints = false;
}

void Player::die() {
  delete this->modeState;
  this->resetPos();
  this->modeState = new DeadState();
}

void Player::takeDamage() {
  this->modeState->takeDamage(this);
}

void Player::takeNormalDamage() {
  this->hp -= 1;

  if (this->hp <= 0) {
    this->die();
  }
}

void Player::normalUpdate() {
  if (this->hasWon) {
    return;
  }
  if (this->dead) {
    return;
  }

  if (this->isClimbing) {
    this->resetVelX();
    this->gravity = 0;
    distance -= 5 * velY;
  } else {
    if (direction == up) {
      distance = 0;
      direction = left;
    }
    this->gravity = 1;
  }

  pos->add(velX, velY);

  if (pos->getX() < 0 or pos->getX() > WIDTH - plyrTex.walkWidth) {
    pos->add(-velX, 0);
  }//WIDTH - texW

  if (isGrounded) { distance += abs(velX); }
  if (distance > 70) { distance = 0; }

  if (counter == 2) {
    if (velY == 5) {
      velY = 4;
      return;
    } //(Velocidad terminal) Este 5 es por la las colisiones (1/4 de la altura de la plataforma)
    velY += this->gravity;
    counter = 0;
    return;
  }
  counter++;
}

int Player::getHp() {
  return this->hp;
}

int Player::getPoints() {
  return this->points;
}

void Player::addPoints(int points)
{
  this->points += points;
}