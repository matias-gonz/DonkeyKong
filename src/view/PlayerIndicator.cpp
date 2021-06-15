#include "PlayerIndicator.h"
#include "ltexture.h"


void PlayerIndicator::show(SDL_Rect* rect, LTexture* box) {

  int boxWidth = box->getWidth();
  int x = rect->x +(rect->w)/2 - boxWidth/2;
  int y = rect->y - box->getHeight() - 2;

  box->render(x,y);
}
