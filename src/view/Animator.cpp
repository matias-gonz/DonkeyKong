
#include "Animator.h"
enum kindOfAnimation { left, right};

Animator::Animator(SDL_Texture *pTexture,int leftStartW,int leftStartH,int rightStartW,int rightStartH,int texW,int texH) {

    this->texture = pTexture;
    this->leftStart[0]= &leftStartW;
    this->leftStart[1] = &leftStartH;
    this->rightStart[0] = &rightStartW;
    this->rightStart[1] = &rightStartH;
    this->texWH[0] = &texW;
    this->texWH[1] = &texH;

}

void Animator::draw(SDL_Renderer *pRenderer, int kind,Position* pos) {
    SDL_Rect srcrect;
    if (kind == left){
        srcrect = {0,0,17,30};//{ *leftStart[0],*leftStart[1] , *texWH[0], *texWH[1]};
    }
    else{
        srcrect = {0,52,17,30};//{ *rightStart[0],*rightStart[1] , *texWH[0], *texWH[1]};
    }

    SDL_Rect dstrect = {static_cast<int>(pos->getX()), static_cast<int>(pos->getY()), 25, 50};
    SDL_RenderCopy(pRenderer, texture, &srcrect, &dstrect);


}

void Animator::start() {

}

void Animator::updateAnimation(int direction) {

}

Animator::Animator() {

}
