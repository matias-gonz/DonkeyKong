//
// Created by matiti on 5/7/21.
//

#include <SDL_rect.h>
#include "PlatformMovement.h"

PlatformMovement::PlatformMovement(bool b) {
    this->isMoving = b;
    this->speed = 1;
}


void PlatformMovement::update(SDL_Rect *rect) {
    if(!this->isMoving){
        return;
    }
    float direction = 1;
    if((rect->y == 350) || (rect->y == 245)){
        if(rect->x == 96){
            rect->x = 864;
        }
        direction = -1;
    }else if(rect->x == 864){
        rect->x = 96;
    }
    rect->x += this->speed*direction;
}
