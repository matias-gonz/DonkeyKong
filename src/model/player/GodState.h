#ifndef TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H

#include "PlayerState.h"

class Player;

class GodState: public PlayerState  {

public:
  explicit GodState();
  ~GodState();
  void takeDamage(Player *pPlayer);
  void update(Player *pPlayer);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H
