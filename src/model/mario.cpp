

#include "mario.h"
#include "Position.h"

Mario::Mario(double xInit, double yInit): pos(xInit,yInit){
    pos = Position(xInit, yInit);

}

void Mario::moveLeft() {
    pos.add(-10,0);
}

void Mario::moveRight() {
    pos.add(10,0);
}

void Mario::jumpUp() {
    if (isGrounded){
        return;
    }
}


