#include "Client.h"
#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(char *port, char *IP) {
  this->quit = false;
  this->gameStarted = false;
  this->running = true;
  this->configuration = new Configuration();
  Logger::startLogger(this->configuration, "client.txt");
  char messageIP[100] = {0};
  strcat(messageIP, "IP del servidor: ");
  strcat(messageIP, IP);
  Logger::log(Logger::Info, messageIP);
  char messagePort[100] = {0};
  strcat(messagePort, "Puerto del servidor: ");
  strcat(messagePort, port);
  Logger::log(Logger::Info, messagePort);
  this->isInLobby = false;
  this->socket = new ClientSocket(port, IP);
  this->positions = Positions();
  this->soundSystem = new SoundSystem();
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
        this->isInLobby = true;
        quit = true;
      } else if (this->loginController->hasAResponse()) {
        char connectionResponseChar = this->loginController->getConnectionResponse();
        viewManagerLogin->close();
        quit = true;
        this->informConnectionOutcome(connectionResponseChar);
      }
    }
  }
  return this->isInLobby;
}

void Client::receive() {
  this->socket->receive(&this->positions, 0);

  if (!socket->isConnected()) {
    this->quit = true;
    this->running = false;
    Logger::log(Logger::Debug, "Client has been disconnected");
    viewManagerGame->renderConnectionLostWindow();
  }
}

void Client::sendString(char *string) {
  this->socket->sndString(string, 0);
}

void Client::send() {
  SDL_Event event;

  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      this->running = false;
      this->socket->snd(&event, 0);
      return;
    }
    if (this->eventIsValid(event)) {
      this->socket->snd(&event, 0);
      printf("manda evento\n");
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
  int clientNumber = this->socket->getClientNumber();

  if(this->positions.transitioningLevel){
    viewManagerGame->renderTransitionWindow(this->positions.playersInfo, this->positions.playerCount);
    this->positions.transitioningLevel=false;
    this->viewManagerGame = new ViewManager(configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
  }
  if(this->positions.endGame){
    viewManagerGame->renderEndGameWindow(this->positions.playersInfo, this->positions.playerCount);
    this->running = false;
  }

  if(!this->positions.endGame) viewManagerGame->renderGameWindow(this->positions, clientNumber);

}

void Client::setSended(bool b) {
  this->sended = b;
}

void Client::goToLobby() {
  Logger::log(Logger::Info, "Entrando al Lobby");
  this->viewManagerLobby = new ViewManager("Lobby", SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED, 600, LOGIN_HEIGHT);
  this->viewManagerLobby->renderLobbyWindow();

  char message = this->socket->rcvChar();
  Logger::log(Logger::Info, "Se recibe confirmacion sobre cantidad de jugadores necesarios alcanzada. Empezando juego");
  viewManagerLobby->close();
  //Check if the server authenticated wrong the user and pass
  if (message != 'c') {
    //return;
  }
  this->viewManagerGame = new ViewManager(configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

}


void Client::informConnectionOutcome(char connectionResponse) {
  if (connectionResponse == 'f') {
    viewManagerLogin->renderWrongCredentialsWindow();
  } else if (connectionResponse == 'a') {
    viewManagerLogin->renderClientAlreadyConnectedWindow();
  } else if (connectionResponse == 'l') {
    viewManagerLogin->renderLobbyIsFullWindow();
  } else {
    viewManagerLogin->renderUnknownResponseWindow(connectionResponse);
  }
}

void Client::playMusic() {
  soundSystem->playGameMusic();
}

void Client::playSounds(){
  int playerNumber = this->socket->getClientNumber();
  soundSystem->reproducePlayerSoundBasedOn(positions.playersInfo[playerNumber].lastEvent);
}

Client::~Client() {
  delete soundSystem;
}
