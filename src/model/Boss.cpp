#include "Boss.h"


Boss::Boss(Position* pos){
    this->pos = pos;
}

void Boss::update() {
    this->movementCounter += 5;

}