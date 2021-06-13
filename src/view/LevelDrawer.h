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


    void drawPlatforms(PlatformContainer *platforms, int count);

    void drawLadders(LadderContainer *ladders, int ladderCount);

    void drawFires(FireContainer *fires, int fireCount);

private:
    TextureManager *textureManager;
    SDL_Renderer *renderer;

    void drawLadder(LadderContainer ladder);
    void drawPlatform(PlatformContainer pPlatform);
    void drawFire(FireContainer fire);
    void drawBarrel(Barrel *barrel);

    int levelnum;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVELDRAWER_H
