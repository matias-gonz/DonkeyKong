#ifndef TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H


#include "PlayerState.h"

class GodState: public PlayerState  {
public:

  explicit GodState();

  ~GodState();

  void takeDamage(Player *player, Entity *pEntity);

  void update(Player *player);

  bool hasWon();

  bool isPlayingLevel(bool b);

  PlayerState *switchGod();

  PlayerState* grabHammer(Hammer ***hammers, int *hammerCount, int index);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H
