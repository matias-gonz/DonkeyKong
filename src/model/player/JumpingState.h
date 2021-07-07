#ifndef TALLER_PROG_I_2021_1C_KIWI_JUMPINGSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_JUMPINGSTATE_H

#include "PlayerState.h"

class JumpingState : public PlayerState{
public:
    JumpingState();
    ~JumpingState();
    void handleInput(Player* player, char input);
    void update(Player* player);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_JUMPINGSTATE_H
