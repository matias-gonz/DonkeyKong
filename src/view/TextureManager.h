#ifndef TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H

#include "SDL2/SDL_image.h"

class TextureManager {

public:
    TextureManager(SDL_Renderer* aRenderer);
    ~TextureManager();

    SDL_Texture* loadTexture(const char* file);

    SDL_Texture* getPlayerTexture();

    SDL_Texture* getPlatformTexture();

    SDL_Texture* getLadderTexture();

    SDL_Texture* getFireTexture();


private:
    SDL_Renderer* renderer;


    void loadPlayerTexture();
    void loadPlatformTexture();
    void loadLadderTexture();
    void loadFireTexture();

    SDL_Texture *playerTexture;
    SDL_Texture *platformTexture;
    SDL_Texture *ladderTexture;
    SDL_Texture *fireTexture;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
