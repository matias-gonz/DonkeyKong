
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include<SDL2/SDL_events.h>
#include "src/view/ltexture.h"
#include "src/model/barrel.h"
#include "src/view/viewManager.h"

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
  //Get rid of preexisting texture
  free();

  //Render text surface
  SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
  if( textSurface != NULL )
  {
    //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
    if( texture == NULL )
    {
      printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
      //Get image dimensions
      width = textSurface->w;
      height = textSurface->h;
    }

    //Get rid of old surface
    SDL_FreeSurface( textSurface );
  }
  else
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
  }


  //Return success
  return texture != NULL;
}
#endif

ViewManager *viewManager = new ViewManager();

int main(int argc, char *args[]) {
  //Start up SDL and create window
  if (!viewManager->successfulInitialitization()) {
    printf("Failed to initialize!\n");
  } else {
    LTexture* barrelTexture = viewManager->loadTexture("/home/nico/Documents/FIUBA/Taller I/TP1/Taller-Prog-I-2021-1C-KIWI/resources/sprites/search.png");
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //The barrel that will be moving around on the screen
    Barrel barrel;
    barrel.setTexture(barrelTexture);

    //While application is running
    while (!quit) {
      //Handle events on queue
      while (SDL_PollEvent(&event) != 0) {
        //User requests quit
        if (event.type == SDL_QUIT) {
          quit = true;
        }
      }

      //Move the barrel
      barrel.move();

      //Clear screen
      SDL_SetRenderDrawColor(viewManager->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(viewManager->getRenderer());

      //Render objects
      barrel.render();

      //Update screen
      SDL_RenderPresent(viewManager->getRenderer());
    }
  }

  //Free resources and close SDL
  viewManager->close();

  return 0;
}
