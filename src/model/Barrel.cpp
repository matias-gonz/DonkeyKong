#include "Barrel.h"

BarrelTexture brrlTex;

Barrel::Barrel()
{
    //Initialize the offsets
    //posX = 200;
    //posY = 0;
}
Barrel::Barrel(Position *position){
    this->width = brrlTex.width;
    this->height = brrlTex.height;

    this->pos = position;
    this->x = position->getX();
    this->y = position->getY();
    this->distance = 0;
    this->velY = 0;
    this->velX = 3;
    this->direction = right;

}
Barrel::~Barrel() {
}

void Barrel::update() {
  this->x = this->pos->getX();
  this->y = this->pos->getY();

  if (this->pos->getX() <= 0 || this->pos->getX()  + this->width >= WIDTH) {
    this->x -= this->velX;
    this->velX = -this->velX;
    this->direction = -this->direction;
    this->distance = 0;
  }
  this->x += this->velX;
  this->y += this->velY;
  this->velY += 1; //gravity

  if(this->velY > 3){
    this->velY = 3;
  }

  this->pos->setX(this->x);
  this->pos->setY(this->y);

  this->distance += abs(velX);

  if (this->distance > 50) {
    this->distance = 0;
  }

}

SDL_Rect *Barrel::getDestRect() {
    auto* rect = new SDL_Rect();
    rect->y = y;
    rect->x = x;
    rect->w = width;
    rect->h = height;
    return rect;
}
void Barrel::moveUp(int i) {
  this->y -= i;
}

void Barrel::resetVelY() {
  this->velY = 0;
}

SDL_Rect Barrel::getRectangle() {
  auto rect = SDL_Rect();
  rect.y = y;
  rect.x = x;
  rect.w = width;
  rect.h = height;
  return rect;
}


