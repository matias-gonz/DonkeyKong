#include "LoginController.h"

LoginController::LoginController() {
  valid = false;
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
    //char* message = credentials.getSocket()->rcvString(0);
    //bool check = !strcmp(message, "Failed connection");
    char connectionResponseChar = credentials.getSocket()->rcvChar();
    bool check = (connectionResponseChar == 'f');
    valid = !check;
  }
}

bool LoginController::isValid() {
  return this->valid;
}
