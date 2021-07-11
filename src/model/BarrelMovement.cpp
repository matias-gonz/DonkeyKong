
#include <SDL_rect.h>
#include "BarrelMovement.h"
#include "../Constants.h"

BarrelMovement::BarrelMovement(int direction) {
  this->direction = direction;
  this->velX = 1;
  this->velY = 1;
  this->distance = 0;
}


void BarrelMovement::update(SDL_Rect *rect) {
  //if(rect->y >= HEIGHT){

  //   rect->y = 0-rect->h;
  //
  //}else
  if (rect->x <= 0 || rect->x >= WIDTH) {
    rect->x -= this->velX;
    this->velX = -this->velX;
  }
  rect->x += this->velX;
  rect->y += this->velY;
  this->velY += 1; //gravity

  this->distance += velX;

  if (distance > 70) {
    this->distance = 0;
  }
}

void BarrelMovement::resetVelY() {
  this->velY = 0;
}

int BarrelMovement::getDistance() {
  return this->distance;
}
