#include "Boss.h"
#include <stdio.h>
enum state{fall, landing,still};

enum direction{left = -1,right = 1};


Boss::Boss(Position* pos){
    this->pos = pos;
    this->state = fall;
    this->direction = left;
    this->velY = 1;
}

void Boss::update() {
    if (this->state == still){
        this->distance += 1;
        if(this->distance > 70){
            this->distance = 0;
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
