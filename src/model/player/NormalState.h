#ifndef TALLER_PROG_I_2021_1C_KIWI_NORMALSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_NORMALSTATE_H


#include "PlayerState.h"

class NormalState: public PlayerState {
public:
    void takeDamage(Player *pPlayer);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_NORMALSTATE_H
