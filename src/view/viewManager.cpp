#include "viewManager.h"

ViewManager::ViewManager() {
  this->success = true;
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->createWindow();
    if (this->window != NULL) this->createRenderer();
    if(this->renderer != NULL) this->initializeRendererColor();
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
    this->success = false;
  }
}

void ViewManager::showSDLError(char *message) {
  printf(message, SDL_GetError());
}

void ViewManager::setTextureLinear() {
  //Set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    printf("Warning: Linear texture filtering not enabled!");
  }
}

void ViewManager::createWindow() {
  this->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->screen_width,
                                  this->screen_height, SDL_WINDOW_SHOWN);
  if (this->window == NULL) {
    this->showSDLError("Window could not be created! SDL Error: %s\n");
    this->success = false;
  }
}

SDL_Renderer* ViewManager::getRenderer() {
  return this->renderer;
}

void ViewManager::createRenderer() {
  this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (this->renderer == NULL) {
    this->showSDLError("Renderer could not be created! SDL Error: %s\n");
    this->success = false;
  }
}

void ViewManager::initializeRendererColor() {
  //Initialize renderer color
  SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    success = false;
  }
}

bool ViewManager::successfulInitialitization() {
  return this->success;
}

void ViewManager::close() {

  //Destroy window
  SDL_DestroyRenderer(ViewManager::renderer);
  SDL_DestroyWindow(this->window);
  this->window = NULL;
  ViewManager::renderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

LTexture* ViewManager::loadTexture(char *path) {
  LTexture* texture = new LTexture();
  texture->setRenderer(this->getRenderer());

  if (!texture->loadFromFile(path)) {
    printf("Failed to load texture!\n");
  }

  return texture;
}


