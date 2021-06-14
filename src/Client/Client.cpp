#include "Client.h"
#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(char *port, char *IP) {
  this->quit = false;
  this->gameStarted = false;
  this->running = true;
  this->configuration = new Configuration();
  Logger::startLogger(this->configuration, "client.txt");

  this->socket = new ClientSocket(port, IP);
  this->viewManagerGame = new ViewManager(configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
}

bool Client::checkCredentials() {
  std::string inputUser;
  std::string inputPass;

  LoginButton *sendButton = new LoginButton();

  if (this->socket->isConnected()) {
    this->loginController = new LoginController();
    this->viewManagerLogin = new ViewManager("Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, LOGIN_WIDTH, LOGIN_HEIGHT, sendButton);

    while (!quit) {
      viewManagerLogin->renderLoginWindow(quit);
      inputUser = viewManagerLogin->returnInputUser();
      inputPass = viewManagerLogin->returnInputPass();
      loginController->handle(sendButton, &inputUser, &inputPass);
      if (loginController->isValid()) {
        viewManagerLogin->close();
        this->viewManagerGame = new ViewManager(configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
        gameStarted = true;
      }
    }
  }
  return true;
}

void Client::receive() {

  this->socket->receive(&positions);
}

bool Client::gameHasStarted() {
  return this->gameStarted;
}

void Client::checkValid() {
}

void Client::send() {
  SDL_Event event;

  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      this->running = false;
      return;
    }
    if (this->eventIsValid(event)) {
      this->socket->snd(&event);
      //return;
    }
  }
}

bool Client::eventIsValid(SDL_Event event) {
  return (event.type == SDL_KEYDOWN or event.type == SDL_KEYUP);
}

bool Client::isRunning() {
  return this->running;
}

void Client::render() {
  viewManagerGame->renderWindow(this->positions);
}

void Client::setSended(bool b) {
  this->sended = b;
}
