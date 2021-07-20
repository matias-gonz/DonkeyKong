#include "NormalState.h"
#include "GodState.h"
#include "HammerState.h"

NormalState::NormalState():PlayerState() {

}

NormalState::~NormalState() {

}


void NormalState::takeDamage(Player *player, Entity *pEntity) {
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

PlayerState *NormalState::switchGod(Player *player) {
  player->switchedToGod();

  return new GodState();
}

PlayerState *NormalState::grabHammer(Hammer ***hammers, int *hammerCount, int index, Player *player) {
  player->grabbedAHammer();

  delete (*hammers)[index];
  (*hammers)[index] = (*hammers)[(*hammerCount)-1];
  (*hammerCount)--;
  *hammers = (Hammer**) realloc(*hammers,(*hammerCount)*sizeof(Hammer*));

  return new HammerState(3);
}

bool NormalState::hasHammer() {
  return false;
}

