#include "Collider.h"

bool Collider::RectCollides(SDL_Rect r1, SDL_Rect r2) {

    return( (r1.x < r2.x + r2.w) && (r1.x + r1.w > r2.x) &&
            (r1.y < r2.y + r2.h) && (r1.y + r1.h > r2.y));
}

void Collider::ResolvePlayerCollision(Player *player, SDL_Rect rect) {
    if(player->getVelY() <= 0){
        return;
    }
    SDL_Rect playerRect = player->getRectangle();
    int dy;

    if(playerRect.y + playerRect.h >= rect.y and playerRect.y + playerRect.h <= rect.y + rect.h/4){
        dy = playerRect.y + playerRect.h - rect.y;
        player->moveUp(dy);
        player->resetVelY();
        player->setGrounded();
    }

}

void Collider::ResolveEnemyCollision(EnemyFire *enemyFire, SDL_Rect rect) {
  if(!enemyFire->isFalling()){
    return;
  }
    SDL_Rect enemyRect = enemyFire->getRectangle();
    int dy;

    if(enemyRect.y + enemyRect.h >= rect.y ){
        dy = enemyRect.y + enemyRect.h - rect.y;
        enemyFire->moveUp(dy);
        enemyFire->resetVelY();
    }

}

void Collider::ResolvePlayerEnemyCollision(Player *player, Entity *entity) {
  player->takeDamage();
}

void Collider::ResolvePlayerFireCollision(Player *player) {
  player->takeDamage();
  player->resetPos();
}

void Collider::ResolveBarrelPLatformCollision(Barrel *pBarrel, SDL_Rect rect) {
  SDL_Rect barrelRect = *pBarrel->getDestRect();
  int dy;
  if(barrelRect.y + barrelRect.h >= rect.y and barrelRect.y + barrelRect.h <= rect.y + rect.h/2){
    dy = barrelRect.y + barrelRect.h - rect.y;
    pBarrel->moveUp(dy);
    pBarrel->resetVelY();
  }

}



