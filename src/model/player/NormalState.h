#ifndef TALLER_PROG_I_2021_1C_KIWI_NORMALSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_NORMALSTATE_H


#include "PlayerState.h"

class NormalState : public PlayerState {
public:

  explicit NormalState();

  ~NormalState();

  void takeDamage(Player *pPlayer);

  void update(Player *player);

  bool hasWon();

  bool isPlayingLevel(bool b);

  PlayerState *switchGod();

  PlayerState* grabHammer(Hammer ***hammers, int *hammerCount, int index);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_NORMALSTATE_H
