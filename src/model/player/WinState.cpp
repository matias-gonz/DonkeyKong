//
// Created by matiti on 7/16/21.
//

#include "WinState.h"

WinState::WinState() {

}

WinState::~WinState() {

}

void WinState::takeDamage(Player *player) {
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

PlayerState *WinState::switchGod() {
  return new WinState();
}

PlayerState* WinState::grabHammer(Hammer ***hammers, int *hammerCount, int index) {
  return new WinState();
}
