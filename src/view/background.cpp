#include "background.h"

void Background::renderImage() {
  //Initialize SDL
  if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  } else {
    //Create window
    window = SDL_CreateWindow("Donkey Kong 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
    SDL_RenderClear(renderer);
  }
}

void Background::closeWindow() {
  SDL_Event event;      //Event handler

  while(event.type != SDL_QUIT){
    while(SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT){
        SDL_Quit();
        exit(1);
      }
      SDL_RenderPresent(renderer);
      // to simulate OP's flashingText()
      SDL_Delay(50);
    }
    SDL_Delay(100);
  }
}

int Background::getHeight() {
  return this->SCREEN_HEIGHT;
}

int Background::getWidth() {
  return this->SCREEN_WIDTH;
}
