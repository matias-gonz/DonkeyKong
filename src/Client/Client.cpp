#include "Client.h"
#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(char *port, char *IP) {
  quit = false;
  gameStarted = false;
  std::string inputUser;
  std::string inputPass;
  this->running = true;
  this->configuration = new Configuration();
  Logger::startLogger(this->configuration, "client.txt");

  //this->socket = new ClientSocket(port, IP);

  ClientSocket *new_socket = new ClientSocket(port, IP);

  this->socket = new_socket;

  //todo: refactorizar a un nuevo objeto solo de login view
  LoginButton *sendButton = new LoginButton();

  if (new_socket->isConnected()) {
    this->loginController = new LoginController();
    this->viewManager = new ViewManager("Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, LOGIN_WIDTH, LOGIN_HEIGHT, sendButton);

    while (!quit) {
      viewManager->renderLoginWindow(quit);
      inputUser = viewManager->returnInputUser();
      inputPass = viewManager->returnInputPass();
      loginController->handle(sendButton, &inputUser, &inputPass);
      if (loginController->isValid()) {
        viewManager->close();

        this->viewManager = new ViewManager(configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
        gameStarted = true;
      }
    }
  }
}

void Client::receive() {
  if (!this->sended) { return; }
  this->socket->receive(&playerPositions);
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
      this->sended = true;
      //printf("snd started\n");
      this->socket->snd(&event);
      //printf("snd finished\n");
      return;
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
  viewManager->renderWindow(this->playerPositions);
}

void Client::setSended(bool b) {
  this->sended = b;
}
