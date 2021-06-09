#include "LoginButton.h"

LoginButton::LoginButton(std::string text, SDL_Renderer* renderer, TTF_Font* font, int posX, int posY, int w, int h){
  this->rect = {posX,posY,w,h};
  this->text = text;
  this->font = font;
  this->renderer = renderer;
  this->isClicked = false;

}