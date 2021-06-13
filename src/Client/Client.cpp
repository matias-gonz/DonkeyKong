#include "Client.h"

Client::Client(char *port, char *IP) {
  quit = false;
  gameStarted = false;
  std::string inputUser;
  std::string inputPass;

  ClientSocket *new_socket = new ClientSocket(port, IP);
  //todo: refactorizar a un nuevo objeto solo de login view
  LoginButton* sendButton = new LoginButton();

  if(new_socket->isConnected()){
    this->loginController = new LoginController();
    this->viewManager = new ViewManager("Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                               SDL_WINDOWPOS_CENTERED, LOGIN_WIDTH, LOGIN_HEIGHT, sendButton);

    while(!quit) {
      viewManager->renderLoginWindow(quit);
      inputUser = viewManager->returnInputUser();
      inputPass = viewManager->returnInputPass();
      loginController->handle(sendButton, &inputUser, &inputPass);
      if(loginController->isValid()) {
        viewManager->close();
        gameStarted = true;
      }
    }
  }
}

void Client::checkValid() {

}

bool Client::gameHasStarted() {
  return this->gameStarted;
}
