#include "EnemyFire.h"
#include <cstdlib>
#include <ctime>
#include "stdio.h"

enum direction {
    left = -1, right = 1
};

EnemyFire::EnemyFire(Position* pos){
    srand(time(NULL));
    this->pos = pos;
    this->velX = rand()%4 + 1;
    this->velY = 0;
    this->distance = 0;
    this->direction = choseDirection();

}
void EnemyFire::update() {
    this->pos->add(this->velX, this->velY);
    distance += abs(velX);

    if (distance > 70) {
        distance = 0;
        direction = -direction;
        velX = -velX;
    }
}

int EnemyFire::choseDirection() {
    srand(time(NULL));
    if (this->distance==0 || this->distance > 60){
        if(rand()%2){return left;}
        return right;
    }
    return this->direction;
}


