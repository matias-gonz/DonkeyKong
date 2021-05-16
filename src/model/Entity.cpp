#include "Entity.h"
enum kindOfAnimation { left = -1, right = 1};

Entity::Entity(Position* pos){
    this->pos = pos;
    velX = 0;
    velY = 0;
    isGrounded = true;
    direction = right;
    distance = 0;
}


double Entity::getXPosition(){
    return pos->getX();
}


double Entity::getYPosition(){
    return pos->getY();
}

Position* Entity::getPos() {
    return pos;
}

int Entity::getDistance() {
    return distance;
}

int Entity::getDirection() {
    return direction;
}

Entity::Entity() {}

