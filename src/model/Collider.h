#ifndef TALLER_PROG_I_2021_1C_KIWI_COLLIDER_H
#define TALLER_PROG_I_2021_1C_KIWI_COLLIDER_H

#include <SDL_rect.h>
#include "player/Player.h"
#include "EnemyFire.h"
#include "Barrel.h"
#include "Hammer.h"

class Collider {

public:
  static bool RectCollides(SDL_Rect rectangle, SDL_Rect anotherRectangle);

  static void ResolvePlayerCollision(Player *Player, SDL_Rect rect);

  static void ResolveEnemyCollision(EnemyFire *pFire, SDL_Rect rect);

    static void ResolveBarrelPLatformCollision(Barrel *pBarrel, SDL_Rect rect);

    static void ResolvePlayerEnemyCollision(Player *pPlayer, Entity *entity);

    static void ResolvePlayerFireCollision(Player *pPlayer);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_COLLIDER_H
