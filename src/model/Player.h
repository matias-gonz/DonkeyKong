
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "Position.h"
#include "../view/Animator.h"

class Player {
    private:
        Position pos = Position(200, 200);
        bool isGrounded;
        int velX;
        int velY;
        int distance;
        int kindOfAnimation;

    public:
        static const int VEL = 5;
        Player();

        void addLeftVel();

        void addRightVel();

        void update();

        void jumpUp();

        void resetVel();

        double getXPosition();

        double getYPosition();

        Position* getPos();

        int getDistance();

        int getDirection();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
