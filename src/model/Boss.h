#ifndef TALLER_PROG_I_2021_1C_KIWI_BOSS_H
#define TALLER_PROG_I_2021_1C_KIWI_BOSS_H

#include "Entity.h"

class Boss:public Entity {
private:
    int movementCounter;
    int state;
    int counter;
public:
    explicit Boss(Position* position);
    void update();
    SDL_Rect getRectangle();
    int getPoints();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_BOSS_H
