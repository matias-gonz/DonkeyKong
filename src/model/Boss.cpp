#include "Boss.h"
#include <stdio.h>
enum state{fall, landing,still};

Boss::Boss(Position* pos){
    this->pos = pos;
    this->state = fall;
    this->direction = 0;
    this->velY = 5;
}

void Boss::update() {
    if (this->state == still){
        this->distance += 5;
        if(this->distance > 70){
            this->distance = 0;
            return;
        }
        return;
    }
    if (this->state == fall){
        this->pos->add(0,this->velY);

        if(this->pos->getY() > 350) {
            this->pos->setY(350);
            this->velY = 0;
            this->state = landing;
        }
    }
    else if(this->state == landing){//no esta cayendo
        this->counter += 5;
        if (this->counter >= 50){
            this->state = still;
        }
    }

}
