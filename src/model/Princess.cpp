#include "Princess.h"

enum direction{left = -1,right = 1};

Princess::Princess(Position* pos){
    this->pos = pos;
    this->direction = 0;
    this->distance =0;
    this->velX = 0;
    this->velY = 0;
    //this->movementCounter = 0;
}
void Princess::update(){

}

SDL_Rect Princess::getRectangle() {
  return SDL_Rect({this->pos->getX(),this->pos->getY(),51, 60});
}
/*
void Princess::update(){
    pos->add(velX,velY);
    this->distance += 1;
    if(this->distance > 30){
        this->distance = 0;
    }

}*/
/*
void Princess::update(){
    this->movementCounter += 2;

    if(this->movementCounter > 40){
        this->direction = -1*this->direction;

        this->movementCounter = 0;
    }
}*/