#include "Hammer.h"

Hammer::Hammer(Position* pos){
  this->pos = pos;
  this->velX = 0;
  this->velY = 1;
  this->distance = 0;
  this->direction = 0;
}

void Hammer::update() {
  this->pos->add(0, this->velY);

  if(this->pos->getY() >= HEIGHT or this->pos->getY() <= 0){
    changeDirection();
    this->pos->add(0, this->velY);
  }
  distance += abs(velY);
  //distance += this->velY;
  if (distance > 20) {
    changeDirection();
  }
  if(this->velY > 3 ){return;}//velocidad terminal
  this->velY += 0;

}

void Hammer::changeDirection(){
  this->direction = -this->direction;
  this->distance = 0;
  this->velY = -this->velY;
}
int Hammer::choseDirection() {

  if(rand()%2 / RAND_MAX){return left;}
  return right;
}

SDL_Rect Hammer::getRectangle() {
  return SDL_Rect({this->pos->getX(),this->pos->getY(),30, 30});
}

void Hammer::moveUp(int dx) {
  //this->pos->add(-dx,0);
}

void Hammer::resetVelX() {
  //this->velX = 0;
}