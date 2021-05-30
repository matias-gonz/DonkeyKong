#ifndef TALLER_PROG_I_2021_1C_KIWI_COLLIDER_H
#define TALLER_PROG_I_2021_1C_KIWI_COLLIDER_H

#include <SDL_rect.h>
#include "Player.h"
#include "EnemyFire.h"

class Collider {

public:
    static bool RectCollides(SDL_Rect rectangle, SDL_Rect anotherRectangle);

    static void ResolvePlayerCollision(Player *Player, SDL_Rect rect);

    static void ResolveEnemyCollision(EnemyFire *pFire, SDL_Rect rect);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_COLLIDER_H
