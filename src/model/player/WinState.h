#ifndef TALLER_PROG_I_2021_1C_KIWI_WINSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_WINSTATE_H


#include "PlayerState.h"

class WinState : public PlayerState {
public:
  explicit WinState();

  ~WinState();

  void takeDamage(Player *player, Entity *pEntity);

  void update(Player *player);

  bool hasWon();

  bool isPlayingLevel(bool b);

  PlayerState *switchGod(Player *player);

  PlayerState* grabHammer(Hammer ***hammers, int *hammerCount, int index, Player *player);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_WINSTATE_H
