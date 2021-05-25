#ifndef TALLER_PROG_I_2021_1C_KIWI_COLLIDER_H
#define TALLER_PROG_I_2021_1C_KIWI_COLLIDER_H

#include <SDL_rect.h>
#include "Player.h"

class Collider {

public:
    static bool RectCollides(SDL_Rect rectangle, SDL_Rect anotherRectangle);

    static void ResolveCollision(Player *Player, SDL_Rect rect);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_COLLIDER_H
