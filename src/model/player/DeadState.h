#ifndef TALLER_PROG_I_2021_1C_KIWI_DEADSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_DEADSTATE_H


#include "PlayerState.h"

class DeadState: public PlayerState  {
    virtual void takeDamage(Player *pPlayer);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_DEADSTATE_H
