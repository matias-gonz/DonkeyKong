#ifndef TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H

#include "SDL2/SDL_image.h"
#include "../../resources/libraries/json.hpp"
#include <stdlib.h>

using json = nlohmann::json;

class TextureManager {

public:
  TextureManager(SDL_Renderer *aRenderer, json sprites);

  ~TextureManager();

  SDL_Texture *loadTexture(std::string path);

  SDL_Texture **getPlayersTextures();

  SDL_Texture *getPlatformTexture(int levelnum);

  SDL_Texture *getLadderTexture(int levelnum);

  SDL_Texture *getFireTexture();

  SDL_Texture *getBarrelTexture();

  SDL_Texture *getEnemyTexture();

  SDL_Texture *getBossTexture();

  SDL_Texture *getPrincessTexture();

  SDL_Texture *getErrorTexture();

  SDL_Texture *getInactivePlayerTexture();

  SDL_Texture *getHeartTexture();

private:
  SDL_Renderer *renderer;
  json sprites;

  void loadPlayersTextures();

  void loadPlatformTexture();

  void loadLadderTexture();

  void loadFireTexture();

  void loadBarrelTexture();

  void loadEnemyTexture();

  void loadBossTexture();

  void loadPrincessTexture();

  void loadHeartTexture();

  std::string loadTextureFromJson(char const *spritePath);

  SDL_Texture *playersTextures[6];
  SDL_Texture *fireTexture;
  SDL_Texture *enemyTexture;
  SDL_Texture *yellowLadderTexture;
  SDL_Texture *cyanLadderTexture;
  SDL_Texture *bluePlatformTexture;
  SDL_Texture *redPlatformTexture;
  SDL_Texture *heartTexture;

  void loadErrorTexture();

  SDL_Texture *errorTexture;
  SDL_Texture *bossTexture;
  SDL_Texture *princessTexture;

  SDL_Texture *barrelTexture;
  SDL_Texture *inectivePlayerTexture;

  void loadInactivePlayerTexture();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_TEXTUREMANAGER_H
