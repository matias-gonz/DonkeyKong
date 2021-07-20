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

  PlayerState *switchGod(Player *player);

  PlayerState* grabHammer(Hammer ***hammers, int *hammerCount, int index, Player *player);

  bool hasHammer();

};


#endif //TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H
