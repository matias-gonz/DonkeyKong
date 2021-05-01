#include "Position.h"


Position::Position(double x, double y){
    setX(x);
    setY(y);
}

double Position::getX(){
    return posX;
}

double Position::getY(){
    return posY;
}

void Position::setX(double x){
    posX = x;
}

void Position::setY(double y){
    posY = y;
}

void Position::add(double x, double y) {
    posX += x;
    posY += y;
}
