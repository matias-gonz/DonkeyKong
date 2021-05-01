#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>

bool running;
const int SCREEN_WIDTH = 980;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void initializeScreen(){
    //Initialize SDL
    if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } else {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);

    }
}
void render() {
    SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

}


void update(){

}
int main( int argc, char* args[] ) {
    running = true;
    initializeScreen();

    SDL_Event event;

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                running = false;
            }
            update();
            render();
        }
        SDL_Delay(1000/60);
    }
    SDL_Quit();

    return 0;
}