
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include<SDL2/SDL_events.h>
#include "src/view/ltexture.h"
#include "src/model/barrel.h"
#include "src/view/viewManager.h"

//The application time based timer
class LTimer {
public:
    //Initializes variables
    LTimer();

    //The various clock actions
    void start();

    void stop();

    void pause();

    void unpause();

    //Gets the timer's time
    Uint32 getTicks();

    //Checks the status of the timer
    bool isStarted();

    bool isPaused();

private:
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};

ViewManager *viewManager = new ViewManager();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface *loadSurface(std::string path);

//Scene textures
LTexture barrilTexture;

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

bool loadMedia() {
  barrilTexture.setRenderer(viewManager->getRenderer());
  //Loading success flag
  bool success = true;

  //Load dot texture
  if (!barrilTexture.loadFromFile(
          "/home/nico/Documents/FIUBA/Taller I/TP1/Taller-Prog-I-2021-1C-KIWI/resources/sprites/search.png")) {
    printf("Failed to load dot texture!\n");
    success = false;
  }

  return success;
}

int main(int argc, char *args[]) {
  //Start up SDL and create window
  if (!viewManager->successfulInitialitization()) {
    printf("Failed to initialize!\n");
  } else {
    //Load media
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      //Main loop flag
      bool quit = false;

      //Event handler
      SDL_Event e;

      //The barrel that will be moving around on the screen
      Barrel barrel;
      barrel.setTexture(&barrilTexture);

      //While application is running
      while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
          //User requests quit
          if (e.type == SDL_QUIT) {
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
  }

  //Free resources and close SDL
  viewManager->close();

  return 0;
}