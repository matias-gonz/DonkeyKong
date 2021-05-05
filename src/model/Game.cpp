#include "Game.h"
#include "../view/TextureLoader.h"
#include "Player.h"

SDL_Renderer* Game::renderer = NULL;
SDL_Texture* sans = NULL;

Game::Game(){}

Game::~Game(){}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        this->window = SDL_CreateWindow(title,xPos,yPos,width,height,flags);

        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        if(this->renderer){
            SDL_SetRenderDrawColor(this->renderer, 255, 128, 128, 255);
        }
        this->isRunning = true;
    }else{
        this->isRunning = false;
    }

}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            this->isRunning = false;
            break;

        default:
            break;
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    player->show(renderer);
    SDL_RenderPresent(renderer);
}

void Game::update() {

}

void Game::clean() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();
}

bool Game::running() {
    return this->isRunning;
}

