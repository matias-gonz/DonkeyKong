#include "GodState.h"
#include "NormalState.h"

GodState::GodState() {

}

GodState::~GodState() {

}

void GodState::takeDamage(Player *player) {
  return;
}

void GodState::update(Player *player) {
  player->normalUpdate();
}

bool GodState::hasWon() {
  return false;
}

bool GodState::isPlayingLevel(bool b) {
  return true;
}

PlayerState *GodState::switchGod() {
  return new NormalState();
}

PlayerState *GodState::grabHammer(Hammer ***hammers, int *hammerCount, int index) {
  return new GodState();
}


