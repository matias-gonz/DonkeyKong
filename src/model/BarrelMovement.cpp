//
// Created by rochi on 14/5/21.
//

#include <SDL_rect.h>
#include "BarrelMovement.h"

BarrelMovement::BarrelMovement(int direction) {
    this->direction = direction;
    this->speed = 1;
}


void BarrelMovement::update(SDL_Rect *rect) {
    if(rect->y >= 576){

       rect->y = 0-rect->h;

    }else if(rect->x == 0 || rect->x == 1024){
        rect->x = 500;
    }
    rect->y += this->speed;
}