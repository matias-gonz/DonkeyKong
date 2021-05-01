#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void renderImage() {
  //Initialize SDL
  if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  } else {
    //Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
    SDL_RenderClear(renderer);
  }
}

void closeWindow() {
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

int main( int argc, char* args[] ) {
  renderImage();
  closeWindow();

  return 0;
}