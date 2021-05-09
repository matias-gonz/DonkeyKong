#ifndef TALLER_PROG_I_2021_1C_KIWI_ENEMY_H
#define TALLER_PROG_I_2021_1C_KIWI_ENEMY_H

#include <string>

/* TODO: Cada enemigo debería ser una instancia de enemigo y se
    devolver esa instancia dependiendo el tipo */
class Enemy {
public:

  void setType(std::string type);

  std::string getType();

private:
  std::string type;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_ENEMY_H
