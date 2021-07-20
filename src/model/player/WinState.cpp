//
// Created by matiti on 7/16/21.
//

#include "WinState.h"

WinState::WinState() {

}

WinState::~WinState() {

}

void WinState::takeDamage(Player *player, Entity *pEntity) {
  return;
}

void WinState::update(Player *player) {
  player->winUpdate();

}

bool WinState::hasWon() {
  return true;
}

bool WinState::isPlayingLevel(bool b) {
  return b;
}

PlayerState *WinState::switchGod(Player *player) {
  return new WinState();
}

PlayerState* WinState::grabHammer(Hammer ***hammers, int *hammerCount, int index, Player *player) {
  return new WinState();
}

bool WinState::hasHammer() {
  return false;
}
