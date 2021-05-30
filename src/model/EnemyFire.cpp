#include "EnemyFire.h"
#include <cstdlib>
#include <ctime>
#include "stdio.h"

enum direction {
    left = -1, right = 1
};

EnemyFire::EnemyFire(Position* pos){
    //srand(time(NULL));
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
    this->velY += 1;
}

int EnemyFire::choseDirection() {
    //srand(time(NULL));
    if (this->distance==0 || this->distance > 60){
        if(rand()%2){return left;}
        return right;
    }
    return this->direction;
}

SDL_Rect EnemyFire::getRectangle() {
    return SDL_Rect({this->pos->getX(),this->pos->getY(),22, 24});
}

void EnemyFire::moveUp(int dy) {
    this->pos->add(0,-dy);
}

void EnemyFire::resetVelY() {
    this->velY = 0;
}


