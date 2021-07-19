#ifndef TALLER_PROG_I_2021_1C_KIWI_HAMMERSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_HAMMERSTATE_H

#include "PlayerState.h"

class HammerState: public PlayerState {
private:
  int durability;

public:
  explicit HammerState(int durability);

  ~HammerState();

  void takeDamage(Player *player, Entity *pEntity);

  void update(Player *player);

  bool hasWon();

  bool isPlayingLevel(bool b);

  PlayerState *switchGod(Player *player);

  PlayerState* grabHammer(Hammer ***hammers, int *hammerCount, int index, Player *player);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_HAMMERSTATE_H
