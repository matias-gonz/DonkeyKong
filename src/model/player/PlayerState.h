#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYERSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYERSTATE_H

#include "Player.h"
#include "../Hammer.h"

class Player;

class PlayerState {
public:

  virtual ~PlayerState() {}

  virtual void takeDamage(Player *pPlayer, Entity *pEntity) = 0;


  virtual void update(Player *player) = 0;

  virtual bool hasWon() = 0;

  virtual bool isPlayingLevel(bool b) = 0;

  virtual PlayerState *switchGod(Player *player) = 0;

  virtual PlayerState* grabHammer(Hammer ***hammers, int *hammerCount, int index, Player *player) = 0;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYERSTATE_H
