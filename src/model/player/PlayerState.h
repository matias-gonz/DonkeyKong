#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYERSTATE_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYERSTATE_H

#include "Player.h"

class Player;

class PlayerState {
public:
    //virtual void handleInput(Player* player, char input);
    //virtual void update(Player* player);
    virtual ~PlayerState(){}

    virtual void takeDamage(Player *pPlayer) = 0;


    virtual void update(Player *player) = 0;

    virtual bool hasWon() = 0;

    virtual bool isPlayingLevel(bool b) = 0;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYERSTATE_H
