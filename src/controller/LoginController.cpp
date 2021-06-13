#include "LoginController.h"

LoginController::LoginController() {
  valid = false;
}

void LoginController::handle(LoginButton *sendButton, std::string *inputUser, std::string *inputPass) {
  //todo: send to the server to compare
  if (sendButton->isClicked()) {
    inputUser->replace(0, 1, "");
    inputPass->replace(0, 1, "");
    printf("user: %s\n", inputUser->c_str());
    printf("pass: %s\n", inputPass->c_str());
    sendButton->unclick();
    this->valid = true;
  }
}

bool LoginController::isValid() {
  return this->valid;
}
