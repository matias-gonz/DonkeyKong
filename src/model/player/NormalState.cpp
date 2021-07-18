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

PlayerState *NormalState::grabHammer(Hammer ***hammers, int *hammerCount, int index) {
  delete (*hammers)[index];
  (*hammers)[index] = (*hammers)[(*hammerCount)-1];
  (*hammerCount)--;
  *hammers = (Hammer**) realloc(*hammers,(*hammerCount)*sizeof(Hammer*));

  return new NormalState();
}

