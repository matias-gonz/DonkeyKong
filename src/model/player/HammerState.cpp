#include "HammerState.h"
#include "GodState.h"

HammerState::HammerState(int durability) {
  this->durability = durability;
}

HammerState::~HammerState() {

}

bool enemyIsInRange(int playerX, int playerW, int playerDir, int enemyX, int enemyW){
  if(playerDir == right){
    return (playerX + playerW - 10 < enemyX);
  }
  return (playerX + 10 > enemyX + enemyW);
}

void HammerState::takeDamage(Player *player, Entity *entity) {
  if(!entity){
    player->takeNormalDamage();
    player->resetPos();
    return;
  }
  SDL_Rect playerRect = player->getRectangle();
  SDL_Rect enemyRect = entity->getRectangle();
  if(this->durability <= 0 || !enemyIsInRange(playerRect.x,playerRect.w,player->getDirection(),enemyRect.x,enemyRect.w)){
    player->takeNormalDamage();
    player->resetPos();
    return;
  }
  player->killedAnEnemy();
  entity->kill();
  player->addPoints(entity->getPoints());
  this->durability--;
}

void HammerState::update(Player *player) {
  player->normalUpdate();
}

bool HammerState::hasWon() {
  return false;
}

bool HammerState::isPlayingLevel(bool b) {
  return true;
}

PlayerState *HammerState::switchGod() {
  return new GodState();
}

PlayerState *HammerState::grabHammer(Hammer ***hammers, int *hammerCount, int index) {
  return new HammerState(this->durability);
}
