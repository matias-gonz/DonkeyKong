#include "SDL2/SDL.h"
#include "../model/Position.h"
#ifndef TALLER_PROG_I_2021_1C_KIWI_ANIMATOR_H
#define TALLER_PROG_I_2021_1C_KIWI_ANIMATOR_H




class Animator {
private:
    int* leftStart[2];
    int* rightStart[2];
    int* texWH[2];
    int separationW;
    int maxAnimation;//cuantos sprites son por animacion
    int currentAnimation;
    SDL_Texture* texture;//sprite sheet
public:
    Animator();
    void start();
    void draw(SDL_Renderer *pRenderer, int kind,Position* pos);
    void updateAnimation(int direction);

    explicit Animator(SDL_Texture *pTexture,int leftStartW,int leftStartH,int rightStartW,int rightStartH,int texW,int texH);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_ANIMATOR_H
