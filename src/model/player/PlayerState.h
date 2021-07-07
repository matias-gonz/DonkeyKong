#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYERSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYERSTATE_H


#include "Player.h"

class PlayerState {
public:
    virtual void handleInput(Player* player, char input);
    virtual void update(Player* player);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYERSTATE_H
