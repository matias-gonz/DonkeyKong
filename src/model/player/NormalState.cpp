#include "NormalState.h"
#include "GodState.h"

NormalState::NormalState():PlayerState() {

}

NormalState::~NormalState() {

}


void NormalState::takeDamage(Player *player) {
  player->takeNormalDamage();
  player->resetPos();
}


void NormalState::update(Player *player) {
  player->normalUpdate();
}

bool NormalState::hasWon() {
  return false;
}

bool NormalState::isPlayingLevel(bool b) {
  return true;
}

PlayerState *NormalState::switchGod() {
  return new GodState();
}

