#include "Position.h"


Position::Position(double x, double y){
    setX(x);
    setY(y);
}

double Position::getX(){
    return myX;
}

double Position::getY(){
    return myY;
}

void Position::setX(double x){
    myX = x;
}

void Position::setY(double y){
    myY = y;
}

