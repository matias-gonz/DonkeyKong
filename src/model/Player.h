
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "Position.h"
#include "../view/Animator.h"
#include "Entity.h"

class Player: public Entity {
    private:


    static const int VEL = 5;
    public:
        Player(Position *pos);

        void addLeftVel();

        void addRightVel();

        void update();

        void jumpUp();

        void resetVel();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
