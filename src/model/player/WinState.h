#ifndef TALLER_PROG_I_2021_1C_KIWI_WINSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_WINSTATE_H


#include "PlayerState.h"

class WinState : public PlayerState {
public:
  explicit WinState();

  ~WinState();

  void takeDamage(Player *player);

  void update(Player *player);

  bool hasWon();

  bool isPlayingLevel(bool b);

  PlayerState *switchGod();

  PlayerState* grabHammer(Hammer ***hammers, int *hammerCount, int index);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_WINSTATE_H
