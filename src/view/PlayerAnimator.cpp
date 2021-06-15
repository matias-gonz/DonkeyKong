#include "PlayerAnimator.h"

PlayerAnimator::PlayerAnimator(SDL_Texture** textures,bool success) {
    this->textures = textures;
    this->success = success;
}

PlayerAnimator::PlayerAnimator() {

}

void PlayerAnimator::draw(SDL_Renderer *pRenderer, int kindOfAnimation, int plyrX, int plyrY, int distance, int i) {
    SDL_Rect* dstrect = new SDL_Rect();
    dstrect->x = plyrX;
    dstrect->y = plyrY;

    SDL_Rect* srcrect = NULL;
    if(this->success){
        srcrect = new SDL_Rect();
    }
    int amount = 0;
    if(distance>=3 && distance <= 30){
        amount = 1;
    }
    else if( distance < 50){
        amount = 2;
    }
    else if(distance < 70) {
        amount = 3;
    }


    if(kindOfAnimation == right or kindOfAnimation == left){
      this->drawWalking(distance, amount, srcrect, dstrect, pRenderer, kindOfAnimation, i);
    }
    else if(kindOfAnimation == up){
      this->drawClimbing(distance, amount, srcrect, dstrect, pRenderer, i);
    }
    else if(kindOfAnimation == jump){
        this->drawJumping();
    }
}

void PlayerAnimator::drawJumping() {

}

void
PlayerAnimator::drawClimbing(int distance, int amount, SDL_Rect *srcrect, SDL_Rect *dstrect, SDL_Renderer *pRenderer,
                             int i) {
    dstrect->w = plyrTex.climbWidth;
    dstrect->h = plyrTex.climbHeight;
    if(srcrect != NULL) {
        srcrect->x = amount*(plyrTex.climbWidth + plyrTex.wSeparation);
        srcrect->y = 2*(plyrTex.climbHeight + plyrTex.hSeparation);
        srcrect->w = plyrTex.climbWidth;
        srcrect->h = plyrTex.climbHeight;
    }
    SDL_RenderCopy(pRenderer, textures[i], srcrect, dstrect);
}

void
PlayerAnimator::drawWalking(int distance, int amount, SDL_Rect *srcrect, SDL_Rect *dstrect, SDL_Renderer *pRenderer,
                            int kindOfAnimation, int i) {
    dstrect->w = plyrTex.walkWidth;
    dstrect->h = plyrTex.walkHeight;
    if(srcrect != NULL) {
        srcrect->x = amount*(plyrTex.walkWidth + plyrTex.wSeparation);
        srcrect->y = 0;

        if(kindOfAnimation == right){
            srcrect->y = plyrTex.walkHeight + plyrTex.hSeparation;
        }
        srcrect->w = plyrTex.walkWidth;
        srcrect->h = plyrTex.walkHeight;
    }
    SDL_RenderCopy(pRenderer, textures[i], srcrect, dstrect);

}