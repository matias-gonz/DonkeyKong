
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "Position.h"
#include "../view/Animator.h"

class Player {
    private:
        Position pos = Position(0, 200);
        bool isGrounded;
        int velX;
        int velY;
        SDL_Texture* playerTexture;
        Animator animator;
        int kindOfAnimation;
        int distance;

    public:
        static const int VEL = 5;
        explicit Player(SDL_Texture* playerTexture);
        void show(SDL_Renderer *pRenderer);

        void addLeftVel();

        void addRightVel();

        void update();

        void jumpUp();

        void resetVel();


};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
