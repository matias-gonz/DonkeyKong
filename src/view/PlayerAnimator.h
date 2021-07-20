#include "SDL2/SDL.h"
#include "../model/Position.h"
#include "../Constants.h"
#include "PlayerIndicator.h"
#include "ltexture.h"

#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYERANIMATOR_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYERANIMATOR_H


class PlayerAnimator {
private:
    int direction;
    SDL_Texture** textures;
    SDL_Texture* inactiveTexture;
    bool success;
    PlayerTexture plyrTex;
    void drawWalking(int distance, int amount, SDL_Rect *srcrect, SDL_Rect *dstrect, SDL_Renderer *pRenderer,
                     int kindOfAnimation, SDL_Texture *playerTexture, LTexture *texture, bool b);
    void drawClimbing(int distance, int amount, SDL_Rect *srcrect, SDL_Rect *dstrect, SDL_Renderer *pRenderer,
                      SDL_Texture *playerTexture, LTexture *texture);
    void drawJumping();
    SDL_Texture *getTextureOfPlayer(int playerNumber, bool isActive);
public:

    PlayerAnimator();
    void draw(SDL_Renderer *pRenderer, int kindOfAnimation, int plyrX, int plyrY, int distance, bool isActive, int i,
              LTexture *box, bool b);
    explicit PlayerAnimator(SDL_Texture **pTextures,SDL_Texture *inactivePlayerTexture,bool success);

    PlayerIndicator *playerIndicator;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYERANIMATOR_H
