//
// Created by matiti on 5/7/21.
//

#include <SDL_rect.h>
#include "PlatformMovement.h"

PlatformMovement::PlatformMovement(int direction) {
    this->direction = direction;
    this->speed = 1;
}


void PlatformMovement::update(SDL_Rect *rect) {
    if(this->direction == 0){
        return;
    }

    if(this->direction == -1){
        if(rect->x == 96){
            rect->x = 864;
        }
    }else if(rect->x == 864){
        rect->x = 96;
    }
    rect->x += this->speed*this->direction;
}
