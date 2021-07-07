#ifndef TALLER_PROG_I_2021_1C_KIWI_WALKINGSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_WALKINGSTATE_H

#include "PlayerState.h"

class WalkingState : public PlayerState {
public:
    WalkingState();
    ~WalkingState();
    void handleInput(Player* player, char input);
    void update(Player* player);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_WALKINGSTATE_H
