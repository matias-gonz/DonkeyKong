#ifndef TALLER_PROG_I_2021_1C_KIWI_BACKGROUND_H
#define TALLER_PROG_I_2021_1C_KIWI_BACKGROUND_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

class Background {
  private:
      //attributes
      int SCREEN_WIDTH = 1280;
      int SCREEN_HEIGHT = 720;
      SDL_Window* window = NULL;
      SDL_Renderer* renderer = NULL;

  public:
      // functions
      Background();

      void renderImage();
      void closeWindow();
      int getWidth();
      int getHeight();
      SDL_Renderer* getRenderer();
};

#endif //TALLER_PROG_I_2021_1C_KIWI_BACKGROUND_H
