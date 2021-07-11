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
  ViewManager(Game *, Configuration *, const char *title, int xPos, int yPos, int width, int height, bool fullscreen);

  ViewManager(Configuration *configurations, char *title, int xPos, int yPos, int width, int height, bool fullscreen);

  ViewManager(const char *title, int xPos, int yPos, int width, int height, LoginButton *sendButton);

  ViewManager(const char *title, int xPos, int yPos, int width, int height);

  ~ViewManager();

  SDL_Renderer *getRenderer();

  bool successfulInitialitization();

  void close();

  LTexture *loadTexture(char *path);

  void drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect);

  void renderLoginWindow(bool &quit);

  void createRenderer();

  std::string returnInputUser();

  std::string returnInputPass();

  void renderConnectionLostWindow();

  void renderLobbyWindow();

  void renderWrongCredentialsWindow();

  void renderClientAlreadyConnectedWindow();

  void renderUnknownResponseWindow(char i);

  void renderLobbyIsFullWindow();

  void renderGameWindow(Positions positions, int clientNumber);

  void renderTransitionWindow();

  void renderEndGameWindow();

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
  bool hasDefaultConfig, isLoginView, isInputUser, isInputPass;
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

  void initializeTextInputs();

  void handleEvents(bool &quit, bool *renderText);

  UsernameBox boxes[MAX_CLIENTS];
  bool isLobbyView;

  void loadLobbyMedia();


  void initializeLobbyTextInputs();

};

#endif //TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H
