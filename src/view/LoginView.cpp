#include "LoginView.h"

LoginView::LoginView() {
  this->viewManager->createWindow( "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  this->viewManager->createRenderer();
}
