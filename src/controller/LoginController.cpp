#include "LoginController.h"

LoginController::LoginController() {
  valid = false;
  this->connectionResponse = 'f';
  this->hasResponse = false;
}

void LoginController::handle(LoginButton *sendButton, std::string *inputUser, std::string *inputPass, credentials &credentials) {
  //todo: send to the server to compare
  if (sendButton->isClicked()) {
    inputUser->replace(0, 1, "");
    inputPass->replace(0, 1, "");
    char* user = (char*)(inputUser->c_str());
    char* pass = (char*)(inputPass->c_str());
    Credentials newCredentials;
    strcpy(newCredentials.username, user);
    strcpy(newCredentials.password, pass);

    credentials.getSocket()->sndCredentials(&newCredentials);
    sendButton->unclick();

    this->connectionResponse = credentials.getSocket()->rcvChar();
    this->hasResponse = true;
    valid = (this->connectionResponse == 'o' );
  }
}

char LoginController::getConnectionResponse() {
  return this->connectionResponse;
}

bool LoginController::isValid() {
  return this->valid;
}

bool LoginController::hasAResponse() {
  return this->hasResponse;
}
