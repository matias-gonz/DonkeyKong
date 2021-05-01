#include "barril.h"

Barril::Barril() {
  //Initialize the offsets
  this->posX = 0;
  this-> posY = 0;

  //Initialize the velocity
  this->velX = 0;
  this->velY = 0;
}

Barril::Barril(Background* background) {
  //Initialize the offsets
  this->posX = 0;
  this->posY = 0;

  //Initialize the velocity
  this->velX = 0;
  this->velY = 0;

  this->background = background;
}

void Barril::handleEvent(SDL_Event &event) {
  //If a key was pressed
  if( event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
    //Adjust the velocity
    switch( event.key.keysym.sym ) {
      case SDLK_UP: velY -= DOT_VEL; break;
      case SDLK_DOWN: velY += DOT_VEL; break;
      case SDLK_LEFT: velX -= DOT_VEL; break;
      case SDLK_RIGHT: velX += DOT_VEL; break;
    }
  } //If a key was released
  else if( event.type == SDL_KEYUP && event.key.repeat == 0 ) {
    //Adjust the velocity
    switch( event.key.keysym.sym ) {
      case SDLK_UP: velY += DOT_VEL; break;
      case SDLK_DOWN: velY -= DOT_VEL; break;
      case SDLK_LEFT: velX += DOT_VEL; break;
      case SDLK_RIGHT: velX -= DOT_VEL; break;
    }
  }
}

void Barril::move() {
  //Move the dot left or right
  posX += velX;

  //If the dot went too far to the left or right
  if( ( posX < 0 ) || ( posX + DOT_WIDTH > background->getWidth() ) )
  {
    //Move back
    posX -= velX;
  }
  //Move the dot up or down
  posY += velY;

  //If the dot went too far up or down
  if( ( posY < 0 ) || ( posY + DOT_HEIGHT > background->getHeight() ) )
  {
    //Move back
    posY -= velY;
  }
}