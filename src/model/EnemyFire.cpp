#include "EnemyFire.h"
#include <cstdlib>
#include "stdio.h"
enum direction {
    left = -1, right = 1
};

EnemyFire::EnemyFire(Position* pos){
    this->pos = pos;
    this->velX = 1;
    this->velY = 0;
    this->distance = 0;
    this->direction = choseDirection();

}
void EnemyFire::update() {
    this->pos->add(this->velX, this->velY);
    distance += abs(velX);
    velX = direction;

    if (distance > 70) {
        distance = 0;
        direction = -direction;
    }
}

int EnemyFire::choseDirection() {
    if (this->distance==0 || this->distance > 60){
        if(rand()%2){return left;}
        return right;
    }
    return this->direction;
}


