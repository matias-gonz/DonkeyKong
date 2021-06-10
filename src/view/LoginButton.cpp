#include "LoginButton.h"

LoginButton::LoginButton(std::string text, SDL_Renderer *renderer, TTF_Font *font, int posX, int posY, int w, int h) {
  this->rect = {posX, posY, w, h};
  this->text = text;
  this->font = font;
  this->renderer = renderer;
  this->clicked = false;

  SDL_Color color = {255, 255, 255, 0xFF};
  SDL_Surface *buttonSurface = TTF_RenderText_Solid(this->font, this->text.c_str(), color);
  if (buttonSurface != NULL) {
    this->texture = SDL_CreateTextureFromSurface(this->renderer, buttonSurface);
    if (this->texture == NULL) {
      Logger::log(Logger::Error, "Error al crear la textura");
    }
    SDL_FreeSurface(buttonSurface);
  } else {
    Logger::log(Logger::Error, "Error al crear la superficie para la textura");
  }
}

void LoginButton::listenToClick(SDL_Event e) {
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    int mousePosX, mousePosY;
    SDL_GetMouseState(&mousePosX, &mousePosY);
    clicked = (mousePosX > this->rect.x && mousePosX < this->rect.x + this->rect.w) &&
              (mousePosY > this->rect.y && mousePosY < this->rect.y + this->rect.h );
  }
}

bool LoginButton::isClicked() {
  return this->clicked;
}

void LoginButton::show() {
  if(isClicked()) {
    SDL_SetRenderDrawColor(renderer, 44, 209, 195, 0);
  }else {
    SDL_SetRenderDrawColor(renderer, 200, 100, 0, 0);
  }
  SDL_RenderFillRect(renderer, &this->rect);
  SDL_SetRenderDrawColor(this->renderer, 60, 125, 200, 0);
  SDL_RenderDrawRect(renderer, &this->rect);
  render(this->texture,this->renderer, this->rect.x + 5,this->rect.y + this->rect.y *0.05 ,this->rect.w * 0.9, this->rect.h * 0.7);
}

void LoginButton::render(SDL_Texture* texture, SDL_Renderer* renderer, int x,int y,int w,int h){
  SDL_Rect renderQuad = { x, y, w, h };
  SDL_Rect* clip = NULL;
  double angle = 0.0;
  SDL_Point* center = NULL;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}
