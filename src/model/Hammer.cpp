#include "Hammer.h"

Hammer::Hammer(Position* pos){
  this->pos = pos;
  this->velX = 0;
  this->velY = 0.5;
  this->distance = 0;
  this->direction = choseDirection();
}

void Hammer::update() {
  this->pos->add(this->velX, this->velY);

  if(this->pos->getY() >= WIDTH or this->pos->getY() <= 0){
    changeDirection();
    this->pos->add(0, this->velY);
  }
  distance += abs(velY);

  if (distance > 10) {
    changeDirection();
  }
  if(this->velY > 5){return;}//velocidad terminal
  this->velY += 1;

}

void Hammer::changeDirection(){
  this->direction = -this->direction;
  this->distance = 0;
  this->velY = -this->velY;
}
int Hammer::choseDirection() {

  if(rand()%2 / RAND_MAX){return up;}
  return down;
}

SDL_Rect Hammer::getRectangle() {
  return SDL_Rect({this->pos->getX(),this->pos->getY(),22, 24});
}

void Hammer::moveUp(int dx) {
  this->pos->add(-dx,0);
}

void Hammer::resetVelX() {
  this->velX = 0;
}