//
// Created by agustin on 9/5/21.
//

#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVELDRAWER_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVELDRAWER_H


#include "../model/Level.h"

class LevelDrawer {

public:
    LevelDrawer(SDL_Renderer *aRenderer, TextureManager *aTexureManager);
    void draw(Level* Level);



private:
    TextureManager *textureManager;
    SDL_Renderer *renderer;

    void drawLadder(Ladder *ladder);
    void drawPlatform(Platform *pPlatform);
    void drawFire(Fire *fire);
    void drawBarrel(Barrel *barrel);

    int levelnum;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVELDRAWER_H
