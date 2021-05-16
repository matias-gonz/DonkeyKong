
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "Position.h"
#include "../view/Animator.h"
#include "Entity.h"

class Player: public Entity {
    private:


    static const int VEL = 5;
    public:
        explicit Player(Position *pos);

        void addLeftVel();

        void addRightVel();

        void jumpUp();

        void resetVel();

        void update();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
