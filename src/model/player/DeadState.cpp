#include "DeadState.h"

DeadState::DeadState():PlayerState() {

}

DeadState::~DeadState() {

}

void DeadState::takeDamage(Player *pPlayer){
  return;
}

void DeadState::update(Player *player) {
  return;
}
