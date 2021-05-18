#include "Position.h"

Position::Position() {
    this->posX = 0;
    this->posY = 0;
}

Position::Position(int x, int y) {
    this->posX = x;
    this->posY = y;
}

int Position::getX() {
    return posX;
}

int Position::getY() {
    return posY;
}

void Position::setX(int x) {
    posX = x;
}

void Position::setY(int y) {
    posY = y;
}

void Position::add(int x, int y) {
    posX += x;
    posY += y;
}
