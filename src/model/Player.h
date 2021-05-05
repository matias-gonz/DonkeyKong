
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "Position.h"

class Player {
    private:
        Position pos = Position(0, 0);
        bool isGrounded;
        int velX;
        int velY;
        void jumpUp();
        void move();
        SDL_Texture* playerTexture;


    public:
        static const int VEL = 10;
        explicit Player(SDL_Texture* playerTexture);
        void handleEvent(SDL_Event &e);
        void show(SDL_Renderer *pRenderer);

        SDL_Texture *getTexture();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
