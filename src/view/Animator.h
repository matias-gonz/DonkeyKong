#include "SDL2/SDL.h"
#include "../model/Position.h"
#ifndef TALLER_PROG_I_2021_1C_KIWI_ANIMATOR_H
#define TALLER_PROG_I_2021_1C_KIWI_ANIMATOR_H




class Animator {
private:
    int leftStartW;
    int rightStartW;
    int leftStartH;
    int rightStartH;
    int texW;
    int texH;
    int separationW;
    bool success;
    int maxAnimation; //cuantos sprites son por animacion
    int currentAnimation;
    SDL_Texture* texture;//sprite sheet
public:
    Animator();
    void draw(SDL_Renderer *pRenderer, int direction,Position* pos,int distance);
    SDL_Rect updateAnimation(int direction,int distance);

    explicit Animator(SDL_Texture *pTexture,int leftStartW,int leftStartH,int rightStartW,int rightStartH,int texW,int texH,int separationW,bool success);


};


#endif //TALLER_PROG_I_2021_1C_KIWI_ANIMATOR_H
