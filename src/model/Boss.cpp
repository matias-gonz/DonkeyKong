#include "Boss.h"
#include <stdio.h>
enum state{fall, landing,still};

enum direction{left = -1,right = 1};


Boss::Boss(Position* pos){
    this->pos = pos;
    this->direction = right;
    this->distance = 0;
    //this->state = still;
    //this->velY = 1;
    //this->counter = 0;
    //this->movementCounter = 0;

}
void Boss::update(){
    this->distance += 1;
    if(this->distance > 30){
        this->distance = 0;
    }

}


SDL_Rect Boss::getRectangle() {
  return SDL_Rect();
}
/*void Boss::update() {
    if (this->state == still){
        this->movementCounter += 1;

        if(this->movementCounter > 50){
            this->direction = -1*this->direction;

            this->movementCounter = 0;
        }
    }
    else if (this->state == fall){
        this->pos->add(0,this->velY);

        if(this->pos->getY() > 350) {
            this->pos->setY(350);
            this->velY = 0;
            this->state = landing;
        }
    }
    else if(this->state == landing){//no esta mostrando

        this->counter += 1;
        if (this->counter >= 50){
            this->state = still;
            this->distance = 0;
            this->direction = right;
        }
    }

}
*/