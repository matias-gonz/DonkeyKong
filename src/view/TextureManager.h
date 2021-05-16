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

    SDL_Texture* getPlatformTexture();

    SDL_Texture* getLadderTexture();

    SDL_Texture* getFireTexture();

private:
    SDL_Renderer* renderer;
    json sprites;

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
