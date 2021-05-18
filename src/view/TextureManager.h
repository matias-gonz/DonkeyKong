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

    SDL_Texture *getLadderTexture(int i);

    SDL_Texture* getFireTexture();

    SDL_Texture* getEnemyTexture();


private:
    SDL_Renderer* renderer;


    void loadPlayerTexture();
    void loadPlatformTexture();
    void loadLadderTexture();
    void loadFireTexture();
    void loadEnemyTexture();

    SDL_Texture *playerTexture;
    SDL_Texture *platformTexture;
    SDL_Texture *fireTexture;
    SDL_Texture *enemyTexture;

    SDL_Texture *yellowLadderTexture;
    SDL_Texture *cyanLadderTexture;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
