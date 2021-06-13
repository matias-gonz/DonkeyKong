#ifndef TALLER_PROG_I_2021_1C_KIWI_LOGINCONTROLLER_H
#define TALLER_PROG_I_2021_1C_KIWI_LOGINCONTROLLER_H

#include <SDL2/SDL_ttf.h>
#include "../view/LoginButton.h"

class LoginController {

public:
  LoginController();

  void handle(LoginButton *sendButton, std::string *inputUser, std::string *inputPass);

  bool isValid();

private:
  bool valid;

};

#endif //TALLER_PROG_I_2021_1C_KIWI_LOGINCONTROLLER_H
