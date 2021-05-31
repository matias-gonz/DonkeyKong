#include "SDL2/SDL.h"
#include "../model/Position.h"
#include "../Constants.h"
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYERANIMATOR_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYERANIMATOR_H


class PlayerAnimator {
private:
    int direction;
    SDL_Texture* texture;
    bool success;
    PlayerTexture plyrTex;
    void drawWalking(int distance, int amount, SDL_Rect *srcrect, SDL_Rect *dstrect, SDL_Renderer *pRenderer,int kindOfAnimation);
    void drawClimbing(int distance, int amount, SDL_Rect *srcrect, SDL_Rect *dstrect, SDL_Renderer *pRenderer);
    void drawJumping();
public:

    PlayerAnimator();
    void draw(SDL_Renderer *pRenderer, int direction,Position* pos,int distance);
    explicit PlayerAnimator(SDL_Texture *pTexture,bool success);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYERANIMATOR_H
