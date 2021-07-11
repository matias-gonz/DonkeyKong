#ifndef TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H


#include "PlayerState.h"

class GodState: public PlayerState  {
public:
    virtual void takeDamage(Player *pPlayer);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_GODSTATE_H
