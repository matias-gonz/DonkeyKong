#include "NormalState.h"

NormalState::NormalState():PlayerState() {

}

NormalState::~NormalState() {

}

void NormalState::takeDamage(Player *pPlayer) {
  pPlayer->takeNormalDamage();
  pPlayer->resetPos();
}

void NormalState::update(Player *player) {
  player->normalUpdate();
}
