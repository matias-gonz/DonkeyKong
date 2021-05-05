
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "Position.h"

class Player {
    private:
        Position pos;
        bool isGrounded;
        int velX;
        int velY;
        void jumpUp();
        void move();


    public:
        static const int VEL = 10;
        Player(double xInit, double yInit);
        void handleEvent(SDL_Event &e);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
