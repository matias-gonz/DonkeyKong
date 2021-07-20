#ifndef TALLER_PROG_I_2021_1C_KIWI_DEADSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_DEADSTATE_H


#include "PlayerState.h"

class DeadState : public PlayerState {

public:
  explicit DeadState();

  ~DeadState();

  void takeDamage(Player *pPlayer, Entity *pEntity);

  void update(Player *player);

  bool hasWon();

  bool isPlayingLevel(bool b);

  PlayerState *switchGod(Player *player);

  PlayerState* grabHammer(Hammer ***hammers, int *hammerCount, int index, Player *player);

  bool hasHammer();

};


#endif //TALLER_PROG_I_2021_1C_KIWI_DEADSTATE_H
