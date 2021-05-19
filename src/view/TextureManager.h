#ifndef TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H

#include "SDL2/SDL_image.h"
#include "../../resources/libraries/json.hpp"

using json = nlohmann::json;

class TextureManager {

public:
    TextureManager(SDL_Renderer* aRenderer, json sprites);
    ~TextureManager();

    SDL_Texture* loadTexture(std::string path);

    SDL_Texture* getPlayerTexture();

    SDL_Texture *getPlatformTexture(int levelnum);

    SDL_Texture *getLadderTexture(int levelnum);

    SDL_Texture* getFireTexture();

    SDL_Texture* getBarrelTexture();

    SDL_Texture* getEnemyTexture();

    SDL_Texture* getBossTexture();

    SDL_Texture* getPrincessTexture();

    SDL_Texture *getErrorTexture();

private:
    SDL_Renderer* renderer;
    json sprites;

    void loadPlayerTexture();
    void loadPlatformTexture();
    void loadLadderTexture();
    void loadFireTexture();
    void loadBarrelTexture();
    void loadEnemyTexture();
    void loadBossTexture();
    void loadPrincessTexture();


    SDL_Texture *playerTexture;
    SDL_Texture *fireTexture;
    SDL_Texture *enemyTexture;
    SDL_Texture *yellowLadderTexture;
    SDL_Texture *cyanLadderTexture;
    SDL_Texture *bluePlatformTexture;
    SDL_Texture *redPlatformTexture;

    void loadErrorTexture();

    SDL_Texture *errorTexture;
    SDL_Texture *bossTexture;
    SDL_Texture *princessTexture;

    SDL_Texture *barrelTexture;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
