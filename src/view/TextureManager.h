#ifndef TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H

#include "SDL2/SDL_image.h"

class TextureManager {

public:
    TextureManager(SDL_Renderer* aRenderer);

    static SDL_Texture* LoadTexture(const char* file);

    static void DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect);

    SDL_Texture* LoadTexture(const char *path, SDL_Renderer *aRenderer);

    SDL_Texture* loadPlayerTexture();

private:
    SDL_Renderer* renderer;

};


#endif //TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
