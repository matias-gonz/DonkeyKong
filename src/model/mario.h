
#ifndef TALLER_PROG_I_2021_1C_KIWI_MARIO_H
#define TALLER_PROG_I_2021_1C_KIWI_MARIO_H


#include "Position.h"

class Mario {
    private:
        Position pos;
        bool isGrounded;

    public:
        Mario(double xInit,double yInit);
        void moveLeft();
        void moveRight();
        void jumpUp();


};


#endif //TALLER_PROG_I_2021_1C_KIWI_MARIO_H
