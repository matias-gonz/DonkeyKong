#ifndef TALLER_PROG_I_2021_1C_KIWI_LOGINCONTROLLER_H
#define TALLER_PROG_I_2021_1C_KIWI_LOGINCONTROLLER_H

#include <SDL2/SDL_ttf.h>

class LoginController {

public:
  LoginController();

  void handle(bool* quit);

private:
  bool isValid;

};

#endif //TALLER_PROG_I_2021_1C_KIWI_LOGINCONTROLLER_H
