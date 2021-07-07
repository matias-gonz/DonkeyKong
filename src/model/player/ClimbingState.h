#ifndef TALLER_PROG_I_2021_1C_KIWI_CLIMBINGSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_CLIMBINGSTATE_H

#include "PlayerState.h"

class ClimbingState : public PlayerState{
public:
    ClimbingState();
    ~ClimbingState();
    void handleInput(Player* player, char input);
    void update(Player* player);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_CLIMBINGSTATE_H
