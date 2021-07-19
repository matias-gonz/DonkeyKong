#include "PlayerEvent.h"

PlayerEvent::PlayerEvent() {
  type = NoEvent;
}

char PlayerEvent::getEventSymbol() {
  return eventSymbol[type];
}

char PlayerEvent::extractEvent() {
  char eventSymbol = this->getEventSymbol();
  type = NoEvent;
  return eventSymbol;
}

void PlayerEvent::playerJumped() {
  type = PlayerJump;
}

void PlayerEvent::playerGotDamaged() {
  type = PlayerWasDamaged;
}

void PlayerEvent::playerGrabbedAHammer() {
  type = PlayerGrabHammer;
}

void PlayerEvent::playerKilledAnEnemy() {
  type = PlayerKilledAnEnemy;
}

void PlayerEvent::playerClimbedALadder() {
  type = PlayerClimbedALadder;
}

void PlayerEvent::playerMutedMusic() {
  type = PlayerMutedMusic;
}

void PlayerEvent::playerStartedGodMode() {
  type = PlayerStartedGodMode;
}

void PlayerEvent::playermutedSoundEffects() {
  type = PlayerMutedSoundEffects;
}

void PlayerEvent::playerDied() {
  type = PlayerLost;
}

void PlayerEvent::playerReachedThePrincess() {
  type = PlayerWon;

}

