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

bool DeadState::hasWon() {
  return false;
}

bool DeadState::isPlayingLevel(bool b) {
  return b;
}

PlayerState *DeadState::switchGod() {
  return new DeadState();
}
