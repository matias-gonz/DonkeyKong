
#include "Animator.h"
#include "stdio.h"
enum kindOfAnimation {
    left = -1, right = 1
};

Animator::Animator(SDL_Texture *pTexture, int leftStartW, int leftStartH, \
                    int rightStartW, int rightStartH, int texW, int texH, int separationW) {

    this->texture = pTexture;
    this->leftStartW = leftStartW;
    this->leftStartH = leftStartH;
    this->rightStartW = rightStartW;
    this->rightStartH = rightStartH;
    this->texW = texW;
    this->texH = texH;
    this->separationW = separationW;

}

void Animator::draw(SDL_Renderer *pRenderer, int direction, Position *pos,int distance) {

    SDL_Rect srcrect = updateAnimation( direction, distance);
    SDL_Rect dstrect = {pos->getX(), pos->getY(), static_cast<int>((1.5*texW)), static_cast<int>((1.5*texH))};
    SDL_RenderCopy(pRenderer, texture, &srcrect, &dstrect);

}


SDL_Rect Animator::updateAnimation(int direction, int distance) {
    if (direction == 0){
        return {0,0,texW,texH};
    }
    int amount = 0;
    if(distance>10 && distance < 30){
        amount = 1;
    }
    else if( distance < 50){
        amount = 2;
    }
    else if(distance < 70) {
        amount = 3;
    }
    if (direction == left){
        return {leftStartW+(amount)*(texW+separationW), leftStartH, texW, texH};

    }
    return {rightStartW+(amount)*(texW+separationW),rightStartH,texW,texH};


}

Animator::Animator() {

}
