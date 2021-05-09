#ifndef TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H

#include "SDL2/SDL_image.h"

class TextureManager {

public:
    TextureManager(SDL_Renderer* aRenderer);

     SDL_Texture* LoadTexture(const char* file);

     void DrawTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect);

     SDL_Texture* loadTexture(const char *path, SDL_Renderer *aRenderer);

    SDL_Texture* loadPlayerTexture();

    SDL_Texture* loadPlatformTexture();

    SDL_Texture* loadLadderTexture();

private:
    SDL_Renderer* renderer;

};


#endif //TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
