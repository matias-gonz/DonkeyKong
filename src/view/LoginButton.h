#ifndef TALLER_PROG_I_2021_1C_KIWI_LOGINBUTTON_H
#define TALLER_PROG_I_2021_1C_KIWI_LOGINBUTTON_H


#include <SDL_rect.h>
#include <string>
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>
#include "../model/Logger.h"

class LoginButton {
public:

  LoginButton(std::string text, SDL_Renderer* renderer, TTF_Font* font, int posX, int posY, int w, int h);

  void listenToClick(SDL_Event e);

  bool isClicked();

  void show();

  void render(SDL_Texture* texture, SDL_Renderer* renderer, int x,int y,int w,int h);

private:
  SDL_Rect rect;
  std::string text;
  SDL_Texture* texture;
  SDL_Renderer* renderer;
  TTF_Font* font;
  bool clicked;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LOGINBUTTON_H
