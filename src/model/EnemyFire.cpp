#include "EnemyFire.h"
#include <cstdlib>
#include <ctime>
#include "stdio.h"

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

    if(this->pos->getX() >= WIDTH or this->pos->getX() <= 0){
        changeDirection();
        this->pos->add(this->velX,0);
    }
    distance += abs(velX);

    if (distance > 70) {
        changeDirection();
    }
    if(this->velY > 5){return;}//velocidad terminal
    this->velY += 1;

}

void EnemyFire::changeDirection(){
    this->direction = -this->direction;
    this->distance = 0;
    this->velX = -this->velX;
}
int EnemyFire::choseDirection() {

    if(rand()%2 / RAND_MAX){return left;}
    return right;
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


