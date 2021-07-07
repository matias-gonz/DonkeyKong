#include "NormalState.h"


void NormalState::takeDamage(Player *pPlayer) {
  pPlayer->takeNormalDamage();
  pPlayer->resetPos();
}
