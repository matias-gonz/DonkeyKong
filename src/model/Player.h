
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "Position.h"

class Player {
    private:
        Position pos = Position(0, 576);
        bool isGrounded;
        int velX;
        int velY;

    public:
        static const int VEL = 1;
        explicit Player();

        void addLeftVel();

        void addRightVel();

        void update();

        void jumpUp();

        void resetVel();

        double getXPosition();

        double getYPosition();


};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
