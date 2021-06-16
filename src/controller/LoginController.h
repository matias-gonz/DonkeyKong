#ifndef TALLER_PROG_I_2021_1C_KIWI_LOGINCONTROLLER_H
#define TALLER_PROG_I_2021_1C_KIWI_LOGINCONTROLLER_H

#include <SDL2/SDL_ttf.h>

#include "Configuration.h"

#include "../view/LoginButton.h"
#include "../Client/credentials.h"

class LoginController {

public:
  LoginController();

  void handle(LoginButton *sendButton, std::string *inputUser, std::string *inputPass, credentials &cred);

  bool isValid();

    char getConnectionResponse();

    bool hasAResponse();

private:
  bool valid;
  Configuration* configuration;
  char connectionResponse;
    bool hasResponse;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_LOGINCONTROLLER_H
