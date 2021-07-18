#include "Animator.h"
#include "stdio.h"
enum kindOfAnimation {
    left = -1, right = 1
};

Animator::Animator(SDL_Texture *pTexture, int leftStartW, int leftStartH, \
                    int rightStartW, int rightStartH, int texW, int texH, int separationW,bool success) {
    //EN VEZ DE TANTAS VARIABLES, PASAR UN STRUCT
    this->texture = pTexture;
    this->leftStartW = leftStartW;
    this->leftStartH = leftStartH;
    this->rightStartW = rightStartW;
    this->rightStartH = rightStartH;
    this->texW = texW;
    this->texH = texH;
    this->separationW = separationW;
    this->success = success;

}

void Animator::draw(SDL_Renderer *pRenderer, int direction, int x, int y,int distance) {
    SDL_Rect* srcrect = NULL;
    if(this->success){
        srcrect = new SDL_Rect();
        *srcrect = updateAnimation( direction, distance);
    }

    int finalTexW = texW;
    int finalTexH = texH;
   // if(texW == 22){
     //   finalTexW = static_cast<int>(1.5*texW);
       // finalTexH = static_cast<int>(1.5*texH);
   // }
    if(texW ==17){
        finalTexW = texW*2;
    }

    SDL_Rect dstrect = {x, y, finalTexW, finalTexH};

    SDL_RenderCopy(pRenderer, texture, srcrect, &dstrect);

}


SDL_Rect Animator::updateAnimation(int direction, int distance) {

    int amount = 0;
    if(distance>=3 && distance <= 30){
        amount = 1;
    }
    else if( distance > 30 and distance < 50){
        amount = 2;
    }
    else if( distance >= 50 and distance < 70) {
        amount = 3;
    }
    if (direction == left){
        return {leftStartW+(amount)*(texW+separationW), leftStartH, texW, texH};

    }
    return {rightStartW+(amount)*(texW+separationW),rightStartH,texW,texH};


}

Animator::Animator() {

}
