#include "DeadState.h"


DeadState::DeadState():PlayerState() {

}

DeadState::~DeadState() {

}

void DeadState::takeDamage(Player *pPlayer, Entity *pEntity) {
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

PlayerState *DeadState::switchGod(Player *player) {
  return new DeadState();
}

PlayerState *DeadState::grabHammer(Hammer ***hammers, int *hammerCount, int index, Player *player) {
  return new DeadState();
}

bool DeadState::hasHammer() {
  return false;
}
