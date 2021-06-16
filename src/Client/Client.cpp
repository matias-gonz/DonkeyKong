#include "Client.h"
#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(char *port, char *IP) {
  this->quit = false;
  this->gameStarted = false;
  this->running = true;
  this->configuration = new Configuration();
  Logger::startLogger(this->configuration, "client.txt");
  this->_isInLobby = false;

  this->socket = new ClientSocket(port, IP);
}

bool Client::checkCredentials() {
  std::string inputUser;
  std::string inputPass;
  credentials *credentials_ins = new credentials();
  LoginButton *sendButton = new LoginButton();

  if (this->socket->isConnected()) {
    this->loginController = new LoginController();
    this->viewManagerLogin = new ViewManager("Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED, LOGIN_WIDTH, LOGIN_HEIGHT, sendButton);

    while (!quit) {
      viewManagerLogin->renderLoginWindow(quit);
      inputUser = viewManagerLogin->returnInputUser();
      inputPass = viewManagerLogin->returnInputPass();
      credentials_ins->initialize(inputUser, inputPass, this->socket);
      loginController->handle(sendButton, &inputUser, &inputPass, *credentials_ins);

      if (loginController->isValid()) {
        viewManagerLogin->close();
        this->_isInLobby = true;
        quit = true;
      }
    }
  }
  return this->_isInLobby;
}

void Client::receive() {
  this->socket->receive(&positions,0);
  printf("%i",this->positions.playerCount);
  if(!socket->isConnected()){
    this->quit = true;
    this->running = false;
    Logger::log(Logger::Debug, "Client has been disconnected");
    viewManagerGame->renderConnectionLostWindow(false);
  }
}

bool Client::gameHasStarted() {
  return this->gameStarted;
}

void Client::checkValid() {
}

void Client::sendString(char* string) {
  this->socket->sndString(string, 0);
}

void Client::send() {
  SDL_Event event;

  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      this->running = false;
      this->socket->snd(&event,0);
      return;
    }
    if (this->eventIsValid(event)) {
      this->socket->snd(&event, 0);
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

void Client::goToLobby() {
  this->viewManagerLobby = new ViewManager("Lobby", SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED, 600, LOGIN_HEIGHT);
  this->viewManagerLobby->renderLobbyWindow();
  /*
  char *message = this->socket->rcvString(0);
  //Check if the server authenticated wrong the user and pass
  bool check = !strcmp(message, "confirmed\a");
  free(message);
  if (!check) {
    return;
  }
  */
  viewManagerLobby->close();

  this->viewManagerGame = new ViewManager(configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

}
