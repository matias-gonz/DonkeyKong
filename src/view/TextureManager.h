#ifndef TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H

#include "SDL2/SDL_image.h"

class TextureManager {

public:
    TextureManager(SDL_Renderer* aRenderer);

     SDL_Texture* loadTexture(const char* file);

    SDL_Texture* loadPlayerTexture();

    SDL_Texture* loadPlatformTexture();

    SDL_Texture* loadLadderTexture();

private:
    SDL_Renderer* renderer;

};


#endif //TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
