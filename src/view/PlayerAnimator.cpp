#include "PlayerAnimator.h"

PlayerAnimator::PlayerAnimator(SDL_Texture **textures, SDL_Texture *inactivePlayerTexture, bool success) {
  this->inactiveTexture = inactivePlayerTexture;
  this->textures = textures;
  this->success = success;
  this->playerIndicator = new PlayerIndicator();
}

PlayerAnimator::PlayerAnimator() {

}

void
PlayerAnimator::draw(SDL_Renderer *pRenderer, int kindOfAnimation, int plyrX, int plyrY, int distance, bool isActive,
                     int i,
                     LTexture *box, bool hasHammer) {
  SDL_Rect *dstrect = new SDL_Rect();
  dstrect->x = plyrX;
  dstrect->y = plyrY;
  SDL_Rect *srcrect = NULL;
  if (this->success) {
    srcrect = new SDL_Rect();
  }
  int amount = 0;
  if (distance >= 3 && distance <= 30) {
    amount = 1;
  } else if (distance < 50) {
    amount = 2;
  } else if (distance < 70) {
    amount = 3;
  }


  SDL_Texture *playerTexture = this->getTextureOfPlayer(i, isActive);

  if (kindOfAnimation == right or kindOfAnimation == left) {
    this->drawWalking(distance, amount, srcrect, dstrect, pRenderer, kindOfAnimation, playerTexture, box, hasHammer);
  } else if (kindOfAnimation == up) {
    this->drawClimbing(distance, amount, srcrect, dstrect, pRenderer, playerTexture, box);
  } else if (kindOfAnimation == jump) {
    this->drawJumping();
  }
}

void PlayerAnimator::drawJumping() {

}

void
PlayerAnimator::drawClimbing(int distance, int amount, SDL_Rect *srcrect, SDL_Rect *dstrect, SDL_Renderer *pRenderer,
                             SDL_Texture *playerTexture, LTexture *texture) {
  dstrect->w = plyrTex.climbWidth;
  dstrect->h = plyrTex.climbHeight;
  if (srcrect != NULL) {
    srcrect->x = amount * (plyrTex.climbWidth + plyrTex.wSeparation);
    srcrect->y = 2 * (plyrTex.climbHeight + plyrTex.hSeparation);
    srcrect->w = plyrTex.climbWidth;
    srcrect->h = plyrTex.climbHeight;
  }
  this->playerIndicator->show(dstrect, texture);
  SDL_RenderCopy(pRenderer, playerTexture, srcrect, dstrect);
}

void
PlayerAnimator::drawWalking(int distance, int amount, SDL_Rect *srcrect, SDL_Rect *dstrect, SDL_Renderer *pRenderer,
                            int kindOfAnimation, SDL_Texture *playerTexture, LTexture *texture, bool hasHammer) {
  dstrect->w = plyrTex.walkWidth;
  dstrect->h = plyrTex.walkHeight;
  if (srcrect != NULL) {
    srcrect->x = amount * (plyrTex.walkWidth + plyrTex.wSeparation);
    srcrect->y = 0;

    if (kindOfAnimation == right) {
      srcrect->y = plyrTex.walkHeight + plyrTex.hSeparation;
    }
    srcrect->w = plyrTex.walkWidth;
    srcrect->h = plyrTex.walkHeight;
  }

  if(hasHammer){
    srcrect->y
    += plyrTex.hammerHeightStart;

  }
  this->playerIndicator->show(dstrect, texture);
  SDL_RenderCopy(pRenderer, playerTexture, srcrect, dstrect);

}

SDL_Texture *PlayerAnimator::getTextureOfPlayer(int playerNumber, bool isActive) {
  //return (isActive) ?  textures[playerNumber] :  this->inactiveTexture;
  if (isActive) {
    return textures[playerNumber];
  } else {
    return this->inactiveTexture;
  }
}
