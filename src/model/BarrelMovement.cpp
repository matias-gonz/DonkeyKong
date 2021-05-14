//
// Created by rochi on 14/5/21.
//

#include <SDL_rect.h>
#include "BarrelMovement.h"

BarrelMovement::BarrelMovement(int direction) {
    this->direction = direction;
    this->speed = 10;
}


void BarrelMovement::update(SDL_Rect *rect) {
    if(rect->y == 1024){
            rect->y = 0;
    }
    rect->y += this->speed;
}