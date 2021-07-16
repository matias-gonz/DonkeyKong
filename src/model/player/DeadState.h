#ifndef TALLER_PROG_I_2021_1C_KIWI_DEADSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_DEADSTATE_H


#include "PlayerState.h"

class DeadState: public PlayerState  {

public:
    explicit DeadState();
    ~DeadState();
    void takeDamage(Player *pPlayer);
    void update(Player *player);
    bool hasWon();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_DEADSTATE_H
