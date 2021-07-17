#ifndef TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H


#include "PlayerState.h"

class GodState: public PlayerState  {
public:

  explicit GodState();

  ~GodState();

  void takeDamage(Player *player);

  void update(Player *player);

  bool hasWon();

  bool isPlayingLevel(bool b);

  PlayerState *switchGod();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H
