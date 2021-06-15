#ifndef TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H

#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
#include "ltexture.h"
#include "../model/Level.h"
#include "../model/Game.h"
#include "LevelDrawer.h"
#include "Animator.h"
#include "../controller/Configuration.h"
#include "../model/Boss.h"
#include "PlayerAnimator.h"
#include "../Constants.h"
#include "../controller/LoginController.h"
#include "LoginButton.h"

class ViewManager {
public:
    ViewManager(Game*, Configuration*, const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

    ViewManager(Configuration *configurations, char *title, int xPos, int yPos, int width, int height, bool fullscreen);

    ViewManager(const char *title, int xPos, int yPos, int width, int height, LoginButton *sendButton);

  ViewManager(const char *title, int xPos, int yPos, int width, int height);

    ~ViewManager();
    SDL_Renderer *getRenderer();

    bool successfulInitialitization();

    void close();

    LTexture* loadTexture(char* path);

    void drawTexture(SDL_Texture *texture, SDL_Rect* srcRect, SDL_Rect* destRect);

    void renderWindow();

    void renderWindow(Positions positions);

  void renderLoginWindow(bool &quit);

  void renderLobbyWindow();

  void createRenderer();

  std::string returnInputUser();

  std::string returnInputPass();

    void renderConnectionLostWindow(bool b);

private:

  SDL_Renderer *renderer;
  SDL_Window *currentWindow;
  bool success;
  int screen_width = WIDTH, screen_height = HEIGHT;
  Game *game;
  TextureManager *textureManager;
  LevelDrawer *levelDrawer;
  //Animator* playerAnimator;
  PlayerAnimator *playerAnimator;
  Animator *enemyAnimator;
  //Animator* bossAnimator;
  //Animator* princessAnimator;
  Configuration *configuration;
  bool hasDefaultConfig, isLoginView, isInputUser, isInputPass, isLobbyView;
  TTF_Font *font;
  int inputUserPosX, inputUserPosY;
  int inputPasswordPosX, inputPasswordPosY;
  std::string inputTextUser, inputTextPass;
  LoginButton *sendButton;

  //Scene textures
  LTexture gPromptUserTextTexture;
  LTexture gInputUserTextTexture;
  LTexture gPromptPasswordTextTexture;
  LTexture gInputPasswordTextTexture;
  LTexture gPromptInfoTextTexture;

  SDL_Window *createWindow(const char *title, int xPos, int yPos, int width, int height, int flags);

  void setTextureLinear();

  void showSDLError(char *message);

  void initializeRendererColor();

  void initializeTTF();

  void loadMedia();

  void loadLobbyMedia();

  void initializeTextInputs();

  void initializeLobbyTextInputs();

  void handleEvents(bool &quit, bool *renderText);

  UsernameBox boxes[MAX_CLIENTS];
};

#endif //TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H
