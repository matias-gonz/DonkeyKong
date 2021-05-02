#ifndef TALLER_PROG_I_2021_1C_KIWI_BARREL_H
#define TALLER_PROG_I_2021_1C_KIWI_BARREL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/background.h"
#include "../view/ltexture.h"

class Barrel {
  public:
      //The dimensions of the dot
      static const int DOT_WIDTH = 50;
      static const int DOT_HEIGHT = 50;

      //Maximum axis velocity of the dot
      static const int DOT_VEL = 10;

      //Initializes the variables
      Barrel();


      //Takes key presses and adjusts the dot's velocity
      void handleEvent(SDL_Event& event);

      //Moves the dot
      void move();

      void setTexture(LTexture textura);

      //Shows the dot on the screen
      void render();


  private:
      int posX, posY;
      int velX, velY;
      Background* background;
      LTexture texturaBarril;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_BARREL_H
