#ifndef TALLER_PROG_I_2021_1C_KIWI_ENEMYFIRE_H
#define TALLER_PROG_I_2021_1C_KIWI_ENEMYFIRE_H

#include <SDL_rect.h>
#include "Entity.h"

class EnemyFire: public Entity{
public:
    explicit EnemyFire(Position* position);
    void update();

    SDL_Rect getRectangle();

    void moveUp(int i);

    void resetVelY();

private:

    int choseDirection();
};




#endif //TALLER_PROG_I_2021_1C_KIWI_ENEMYFIRE_H
