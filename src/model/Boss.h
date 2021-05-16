#ifndef TALLER_PROG_I_2021_1C_KIWI_BOSS_H
#define TALLER_PROG_I_2021_1C_KIWI_BOSS_H

#include "Entity.h"

class Boss:public Entity {
private:
    int movementCounter;
public:
    explicit Boss(Position* position);
    void update();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_BOSS_H
