#include "GodState.h"
#include "NormalState.h"

GodState::GodState() {

}

GodState::~GodState() {

}

void GodState::takeDamage(Player *player, Entity *pEntity) {
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

PlayerState *GodState::switchGod(Player *player) {
  return new NormalState();
}

PlayerState *GodState::grabHammer(Hammer ***hammers, int *hammerCount, int index, Player *player) {
  return new GodState();
}


