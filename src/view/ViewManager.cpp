#include "ViewManager.h"

//Player
const int LEFTSTARTW = 0;
const int LEFTSTARTH = 0;
const int RIGHTSTARTW = 0;
const int RIGHTSTARTH = 52;
const int SEPARATIONW = 5;
const int texW = 17;
const int texH = 30;

ViewManager::ViewManager(Configuration *configurations, char *title, int xPos, int yPos, int width, int height,
                         bool fullscreen) {
  this->screen_width = width;
  this->screen_height = height;
  this->configuration = configurations;
  this->isLoginView = false;
  this->hasDefaultConfig = false;

  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  this->success = true;
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->currentWindow = this->createWindow(title, xPos, yPos, width, height, flags);
    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) this->initializeRendererColor();
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
    this->success = false;
  }

  this->textureManager = new TextureManager(this->renderer, this->configuration->getSprites());
  this->levelDrawer = new LevelDrawer(this->renderer, this->textureManager);

  SDL_Texture **playerTextures = this->textureManager->getPlayersTextures();
  bool playerTextureSuccess = true;
  for (int i = 0; i < 5; i++) {
    if (!playerTextures[i]) {
      playerTextures[i] = this->textureManager->getErrorTexture();
      playerTextureSuccess = false;
    }
  }

  SDL_Texture *inactivePlayerTexture = this->textureManager->getInactivePlayerTexture();
  if (!inactivePlayerTexture) {
    inactivePlayerTexture = this->textureManager->getErrorTexture();
  }


  SDL_Texture *enemyTexture = this->textureManager->getEnemyTexture();
  bool enemyTextureSuccess = true;
  if (!enemyTexture) {
    enemyTexture = this->textureManager->getErrorTexture();
    enemyTextureSuccess = false;
  }

  SDL_Texture *barrelTexture = this->textureManager->getBarrelTexture();
  bool barrelTextureSuccess = true;

  if (!barrelTexture) {
    barrelTexture = this->textureManager->getErrorTexture();
    barrelTextureSuccess = false;
  }

  SDL_Texture *hammerTexture = this->textureManager->getHammerTexture();
  bool hammerTextureSuccess = true;
  if (!hammerTexture) {
    hammerTexture = this->textureManager->getErrorTexture();
    hammerTextureSuccess = false;
  }

  //this->playerAnimator = new Animator(playerTexture,LEFTSTARTW,LEFTSTARTH,RIGHTSTARTW,RIGHTSTARTH,texW,texH,SEPARATIONW,playerTextureSuccess);
  this->playerAnimator = new PlayerAnimator(playerTextures, inactivePlayerTexture, success);
  this->enemyAnimator = new Animator(enemyTexture, 0, 0, 0, 25, 22, 24, 2, enemyTextureSuccess);

  BarrelTexture brrlTex;
  this->barrelAnimator = new Animator(barrelTexture, 0, 0, 0, brrlTex.height + brrlTex.hSep, brrlTex.width, brrlTex.height, brrlTex.wSep, barrelTextureSuccess);
  char **users = this->configuration->getUsers();
  //aca creo boxes

  SDL_Color textColor = {255, 255, 0, 0xFF};

  this->font = TTF_OpenFont("resources/fonts/font.ttf", 20);
  this->playersFont = TTF_OpenFont("resources/fonts/font.ttf", 30);

  for (int i = 0; i < MAX_CLIENTS; i++) {
    //std::string u;
    //u.append(users[i]);
    this->boxes[i].box.loadFromRenderedText(users[i], textColor, this->font, this->renderer);
    strcpy(this->boxes[i].username, users[i]);
  }
  //aca libero users
  for (int i = 0; i < MAX_CLIENTS; i++) {
    free(users[i]);
  }
  free(users);
  //ESTOS NO FUNKAN
  //this->bossAnimator = new Animator(this->textureManager->getBossTexture(),0,0,170,0,170,119,0);
  //this->princessAnimator = new Animator(this->textureManager->getPrincessTexture(),4,4,27,4,15,22,0);
}

ViewManager::ViewManager(const char *title, int xPos, int yPos, int width, int height, LoginButton *sendButton) {

  this->screen_width = width;
  this->screen_height = height;
  this->hasDefaultConfig = false;
  this->isLoginView = true;
  this->success = true;
  this->inputTextUser = ">";
  this->inputTextPass = ">";

  int flags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->currentWindow = this->createWindow(title, xPos, yPos, width, height, SDL_WINDOW_SHOWN);
    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) this->initializeRendererColor();
    this->initializeTTF();
    this->loadMedia();
    this->sendButton = sendButton;
    this->sendButton->initialize("Enviar", this->renderer, this->font, 160, 240, 100, 40);
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
    this->success = false;
  }
}

void ViewManager::showSDLError(char *message) {
  printf(message, SDL_GetError());
}

void ViewManager::setTextureLinear() {
  //Set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    printf("Warning: Linear texture filtering not enabled!");
  }
}

SDL_Window *ViewManager::createWindow(const char *title, int xPos, int yPos, int width, int height, int flags) {

  SDL_Window *currentWindow = SDL_CreateWindow(title, xPos, yPos, this->screen_width,
                                               this->screen_height, flags);

  if (currentWindow == NULL) {
    this->showSDLError("Window could not be created! SDL Error: %s\n");
    this->success = false;
  }
  return currentWindow;
}

SDL_Renderer *ViewManager::getRenderer() {
  return this->renderer;
}

void ViewManager::createRenderer() {
  this->renderer = SDL_CreateRenderer(this->currentWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC |
                                                               SDL_RENDERER_TARGETTEXTURE);

  if (this->renderer == NULL) {
    this->showSDLError("Renderer could not be created! SDL Error: %s\n");
    this->success = false;
  }
}

void ViewManager::initializeRendererColor() {
  //Initialize renderer color
  if (this->hasDefaultConfig) {
    SDL_SetRenderDrawColor(this->renderer, 200, 100, 200, 100);
  } else {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
  }
  if (this->isLoginView) {
    SDL_SetRenderDrawColor(this->renderer, 60, 125, 200, 0);
  }
  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    success = false;
  }
}

bool ViewManager::successfulInitialitization() {
  return this->success;
}

void ViewManager::close() {
  SDL_DestroyWindow(this->currentWindow);
  SDL_DestroyRenderer(this->renderer);
  this->renderer = NULL;
  this->currentWindow = NULL;
}

void ViewManager::drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect) {
  SDL_RenderCopy(renderer, texture, srcRect, destRect);
}

void ViewManager::renderTransitionWindow(PlayersInformation playerInfo[], int playerCount) {
  //Clear the renderer and window
  this->close();
  //Create new  er and window
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->screen_width = TRANSITION_WIDTH;
    this->screen_height = TRANSITION_HEIGHT;
    this->currentWindow = this->createWindow("Donkey Kong - Loading next Level", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             TRANSITION_WIDTH, TRANSITION_HEIGHT, 0);

    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) SDL_SetRenderDrawColor(this->renderer, 60, 125, 200, 0);
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
  }

  //Set font color, size and text
  SDL_Color textColor = {255, 255, 255, 0xFF};
  TTF_Font *fontPlayerInfo = TTF_OpenFont("resources/fonts/font.ttf", 25);
  TTF_Font *fontMsjInformativo = TTF_OpenFont("resources/fonts/font.ttf", 35);

  SDL_RenderClear(this->renderer);

  LTexture mensajeInformativo;
  mensajeInformativo.loadFromRenderedText(" Puntajes parciales", textColor, fontMsjInformativo, this->renderer);
  mensajeInformativo.render(this->screen_width / 2 - mensajeInformativo.getWidth()/2,
                            mensajeInformativo.getHeight()/2);

  int separator = 0;

  for (int i = 0; i < playerCount; i++) {

    std::string obtuvo = " obtuvo ";
    std::string puntos = " puntos ";
    std::string playerText = playerInfo[i].username + obtuvo + std::to_string(playerInfo[i].points) + puntos;

    //SDL_Rect heartDstrect = {0, 0, (int) (1.5 * texW), (int) (0.7*texH)};
    //SDL_RenderCopy(this->renderer, this->textureManager->getHeartTexture(), NULL, &heartDstrect);

    usernameAndPointsTexture[i].loadFromRenderedText(playerText.c_str(), textColor, fontPlayerInfo, this->renderer);
    usernameAndPointsTexture[i].render((this->screen_width / 2) - (usernameAndPointsTexture[i].getWidth() / 2),
                                       this->screen_height / (playerCount + 1) + separator);
    separator += 50;
  }

  SDL_RenderPresent(renderer);
  TTF_CloseFont(fontPlayerInfo);
  TTF_CloseFont(fontMsjInformativo);

  SDL_Delay(5000);
  this->close();
}

SDL_Event ViewManager::renderEndGameWindow(PlayersInformation playerInfo[], int playerCount, int clientNumber, std::string estado) {
  //Clear the renderer and window
  this->close();
  //Create new renderer and window
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->screen_width = WIDTH;
    this->screen_height = HEIGHT;
    this->currentWindow = this->createWindow("Donkey Kong - End Game", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             CONNECTION_LOST_WIDTH, CONNECTION_LOST_HEIGHT, 0);

    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) SDL_SetRenderDrawColor(this->renderer, 60, 125, 200, 0);
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
  }

  SDL_RenderClear(this->renderer);

  //Set font color, size and text
  SDL_Color textColor = {255, 255, 255, 0xFF};

  TTF_Font *fontMsjInformativo = TTF_OpenFont("resources/fonts/font.ttf", 50);

  std::string stateText = playerInfo[clientNumber].username + estado;
  LTexture mensajeInformativo;
  mensajeInformativo.loadFromRenderedText(stateText, textColor, fontMsjInformativo, this->renderer);
  mensajeInformativo.render(this->screen_width / 2 - mensajeInformativo.getWidth() / 2,
                            20);

  TTF_CloseFont(fontMsjInformativo);

  TTF_Font *fontPlayerInfo = TTF_OpenFont("resources/fonts/font.ttf", 40);

  int separator = 0;

  //PlayersInformation playersInfoOrdered = orderPlayerInfoByPoints( playerInfo[]);

  for (int i = playerCount; i > 0; i--) {

    std::string obtuvo = " obtuvo ";
    std::string puntos = " puntos ";
    std::string playerText = playerInfo[i-1].username + obtuvo + std::to_string(playerInfo[i-1].points) + puntos;

    //SDL_Rect heartDstrect = {0, 0, (int) (1.5 * texW), (int) (0.7*texH)};
    //SDL_RenderCopy(this->renderer, this->textureManager->getHeartTexture(), NULL, &heartDstrect);

    usernameAndPointsTexture[i-1].loadFromRenderedText(playerText.c_str(), textColor, fontPlayerInfo, this->renderer);
    usernameAndPointsTexture[i-1].render((this->screen_width / 2) - (usernameAndPointsTexture[i-1].getWidth() / 2),
                                       this->screen_height / (playerCount + 1) + separator);

    separator += 50;
  }
  TTF_CloseFont(fontPlayerInfo);
  SDL_RenderPresent(renderer);

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0 && !quit) {
      quit = e.type == SDL_QUIT;
    }
  }

  return e;
}

void ViewManager::renderGameWindow(Positions positions, int clientNumber) {
  SDL_RenderClear(this->renderer);
/*
    //this->princessAnimator->draw(this->renderer,princessDirection,princessPos,princessDistance);
    //this->bossAnimator->draw(this->renderer,bossDirection,bossPos,bossDistance);
*/
  this->renderPlayersInfo(positions.playersInfo, positions.playerCount, clientNumber);
  this->levelDrawer->drawLadders(positions.ladders, positions.ladderCount);
  this->levelDrawer->drawPlatforms(positions.platforms, positions.platformCount);
  SDL_Rect bossDstrect = {positions.bossInfo.x, positions.bossInfo.y, 170, 119};;
  SDL_RenderCopy(this->renderer, this->textureManager->getBossTexture(), NULL, &bossDstrect);

  SDL_Rect princessDstrect = {positions.princessInfo.x, positions.princessInfo.y, (int) (3 * texW), (int) (2 * texH)};;
  SDL_RenderCopy(this->renderer, this->textureManager->getPrincessTexture(), NULL, &princessDstrect);
  this->levelDrawer->drawFires(positions.fires, positions.fireCount);
  // render every player except "me"
  for (int i = 0; i < positions.playerCount; i++) {
    int boxIndex;
    if (i != clientNumber) {
      for (int j = 0; j < MAX_CLIENTS; j++) {
        if (strcmp(this->boxes[j].username, positions.playersInfo[i].username) == 0) {
          boxIndex = j;
          break;
        }
      }
      if(positions.playersInfo[i].alive) {
        this->playerAnimator->draw(this->renderer, positions.playersInfo[i].direction,
                                   positions.playersInfo[i].x,
                                   positions.playersInfo[i].y, positions.playersInfo[i].distance,
                                   positions.playersInfo[i].isActive, i, &this->boxes[boxIndex].box,
                                   positions.playersInfo[i].hammer);
      }
    }
  }
  for (int i = 0; i < positions.fireEnemyCount; i++) {
    this->enemyAnimator->draw(this->renderer, positions.fireEnemies[i].direction, positions.fireEnemies[i].x,
                              positions.fireEnemies[i].y, positions.fireEnemies[i].distance);
  }

  for (int i = 0; i < positions.barrelCount; i++) {
    this->barrelAnimator->draw(this->renderer, positions.barrels[i].direction, positions.barrels[i].x,
                               positions.barrels[i].y, positions.barrels[i].distance);
  }

  for(int i=0; i < positions.hammersCount; i++){
    SDL_Rect hammerRect = SDL_Rect({positions.hammers[i].x,positions.hammers[i].y, 25, 25});
    SDL_RenderCopy(this->renderer, this->textureManager->getHammerTexture(), NULL, &hammerRect);
  }


  // render my player
  int boxPosition;
  for (int j = 0; j < MAX_CLIENTS; j++) {
    if (strcmp(this->boxes[j].username, positions.playersInfo[clientNumber].username) == 0) {
      boxPosition = j;
      break;
    }
  }

  if(positions.playersInfo[clientNumber].alive) {
    this->playerAnimator->draw(this->renderer, positions.playersInfo[clientNumber].direction,
                               positions.playersInfo[clientNumber].x,
                               positions.playersInfo[clientNumber].y, positions.playersInfo[clientNumber].distance,
                               positions.playersInfo[clientNumber].isActive, clientNumber,
                               &this->boxes[boxPosition].box, positions.playersInfo[clientNumber].hammer);
  }

  SDL_RenderPresent(renderer);

}

void ViewManager::renderPlayersInfo(PlayersInformation *playersInfo, int playersCount, int clientNumber) {
  SDL_Color textColor = {255, 255, 255, 0xFF};
  SDL_Color myTextColor = {60, 120, 0, 0xFF};
  std::string space = "    ";
  for (int i = 0; i < playersCount; i++) {
    // Create playerName with points
    std::string playerName = playersInfo[i].username;
    std::string playerText = playerName.substr(0, 4) + space + std::to_string(playersInfo[i].points);
    for(int i = 0; i < playerText.size(); i++) {
      playerText.at(i) = toupper(playerText.at(i));
    }
    //Render players info
    if(i == clientNumber) {
      playersInfoTexture[i].loadFromRenderedText(playerText.c_str(), myTextColor, this->playersFont, this->renderer);
    } else {
      playersInfoTexture[i].loadFromRenderedText(playerText.c_str(), textColor, this->playersFont, this->renderer);
    }
    playersInfoTexture[i].render(((this->screen_width/(playersCount+1))*(i+1))-playersInfoTexture[i].getWidth()/2,  0);
    int heartSeparator = 20;
    for (int j = 0; j < playersInfo[i].hp; j++) {
      SDL_Rect heartDstrect = {((this->screen_width/(playersCount+1))*(i+1))-playersInfoTexture[i].getWidth()/2+heartSeparator, 30, (int) (1.5 * texW), (int) (0.7*texH)};
      SDL_RenderCopy(this->renderer, this->textureManager->getHeartTexture(), NULL, &heartDstrect);
      heartSeparator += 30;
    }
  }
}

void ViewManager::renderLoginWindow(bool &quit) {
  if (this->success && !quit) {
    SDL_Color textColor = {255, 255, 255, 0xFF};
    gInputUserTextTexture.loadFromRenderedText(inputTextUser.c_str(), textColor, this->font, this->renderer);
    gInputPasswordTextTexture.loadFromRenderedText(inputTextPass.c_str(), textColor, this->font, this->renderer);
    SDL_StartTextInput();
    this->initializeTextInputs();

    bool renderText = false;
    this->handleEvents(quit, &renderText);

    if (renderText) {
      if (inputTextUser != "") {
        gInputUserTextTexture.loadFromRenderedText(inputTextUser.c_str(), textColor, this->font,
                                                   this->renderer);
      } else {
        gInputUserTextTexture.loadFromRenderedText(" ", textColor, this->font, this->renderer);
      }
      if (inputTextPass != "") {
        gInputPasswordTextTexture.loadFromRenderedText(inputTextPass.c_str(), textColor, this->font,
                                                       this->renderer);
      } else {
        gInputPasswordTextTexture.loadFromRenderedText(" ", textColor, this->font, this->renderer);
      }
    }
    SDL_RenderClear(this->renderer);
    gPromptUserTextTexture.render(this->inputUserPosX, this->inputUserPosY);
    gInputUserTextTexture.render(this->inputUserPosX, this->inputUserPosY + gPromptUserTextTexture.getHeight());
    gPromptPasswordTextTexture.render(this->inputPasswordPosX, this->inputPasswordPosY);
    gInputPasswordTextTexture.render(this->inputPasswordPosX,
                                     this->inputPasswordPosY + gInputPasswordTextTexture.getHeight());
    sendButton->show();

    //Update screen
    SDL_RenderPresent(this->renderer);

    //Disable text input
    SDL_StopTextInput();
  }
}

void ViewManager::renderLobbyWindow() {
  //Create new renderer and window
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) SDL_SetRenderDrawColor(this->renderer, 0, 100, 100, 0);
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
  }
  SDL_RenderClear(this->renderer);

  SDL_Color textColor = {0, 0, 0, 0xFF};
  TTF_Font *font = TTF_OpenFont("resources/fonts/font.ttf", 20);
  LTexture errorMessage;
  errorMessage.loadFromRenderedText("Esperando a que ingresen mas usuarios...", textColor, font, this->renderer);

  //Render window with exit button
  SDL_Event e;
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0 && !quit) {
      quit = e.type == SDL_QUIT;
    }
    errorMessage.render(errorMessage.getWidth() / 10, errorMessage.getHeight() + 80);
    SDL_RenderPresent(renderer);
  }
}

void ViewManager::initializeTextInputs() {
  this->inputUserPosX = (this->screen_width - gPromptUserTextTexture.getWidth()) / 2;
  this->inputUserPosY = 0;
  int inputPosY = this->inputUserPosY + gPromptUserTextTexture.getHeight();
  this->inputUserPosX = (this->screen_width - gPromptPasswordTextTexture.getWidth()) / 2;
  this->inputUserPosY = inputPosY + 20;
  this->inputPasswordPosX = (this->screen_width - gPromptPasswordTextTexture.getWidth()) / 2;
  this->inputPasswordPosY = inputPosY + 100;

}

void ViewManager::handleEvents(bool &quit, bool *renderText) {

  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    sendButton->listenToClick(e);
    if (e.type == SDL_QUIT || sendButton->isClicked()) {
      quit = true;
    } else if (e.type == SDL_KEYDOWN) {
      if (e.key.keysym.sym == SDLK_BACKSPACE) {

        if (isInputUser && inputTextUser.length() > 1) inputTextUser.pop_back();
        if (isInputPass && inputTextPass.length() > 1) inputTextPass.pop_back();
        *renderText = true;
      } else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
        SDL_SetClipboardText(inputTextUser.c_str());
      } else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
        inputTextUser = SDL_GetClipboardText();
        *renderText = true;
      }
    } else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
      int mousePosX, mousePosY;
      SDL_GetMouseState(&mousePosX, &mousePosY);
      int inputUserPosY = this->inputUserPosY + gPromptUserTextTexture.getHeight();
      int inputPassPosY = this->inputPasswordPosY + gPromptPasswordTextTexture.getHeight();
      if ((mousePosX > this->inputUserPosX - 100 && mousePosX < this->inputUserPosX + 200) &&
          (mousePosY > inputUserPosY && mousePosY < inputUserPosY + gInputUserTextTexture.getHeight())) {
        isInputUser = true;
      } else {
        isInputUser = false;
      }

      if ((mousePosX > this->inputPasswordPosX - 100 && mousePosX < this->inputPasswordPosX + 200) &&
          (mousePosY > inputPassPosY && mousePosY < inputPassPosY + gInputPasswordTextTexture.getHeight())) {
        isInputPass = true;
      } else {
        isInputPass = false;
      }
    } else if (e.type == SDL_TEXTINPUT) {
      if (e.type == SDL_TEXTINPUT) {
        if (!(SDL_GetModState() & KMOD_CTRL &&
              (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' ||
               e.text.text[0] == 'V'))) {
          if (isInputUser && inputTextUser.length() < 15) inputTextUser += e.text.text;
          if (isInputPass && inputTextPass.length() < 15) inputTextPass += e.text.text;
          *renderText = true;
        }
      }
    }
  }
}

void ViewManager::initializeTTF() {
  //Initialize SDL_ttf
  if (TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    this->success = false;
  }
}

std::string ViewManager::returnInputUser() {
  return this->inputTextUser;
}

std::string ViewManager::returnInputPass() {
  return this->inputTextPass;
}

void ViewManager::loadMedia() {
  //Open the font
  this->font = TTF_OpenFont("resources/fonts/font.ttf", 28);

  if (this->font == NULL) {
    printf("Failed to load product sans font! SDL_ttf Error: %s\n", TTF_GetError());
    this->success = false;
  } else {
    //Render the prompt
    SDL_Color textColor = {0, 0, 0, 0xFF};
    if (!this->gPromptUserTextTexture.loadFromRenderedText("Ingrese usuario:", textColor, this->font,
                                                           this->renderer)) {
      printf("Failed to render user prompt text!\n");
      this->success = false;
    }
    if (!this->gPromptPasswordTextTexture.loadFromRenderedText("Ingrese contrasenia:", textColor, this->font,
                                                               this->renderer)) {
      printf("Failed to render password prompt text!\n");
      this->success = false;
    }
  }
}

ViewManager::~ViewManager() {
  delete this->playerAnimator;
  //delete this->renderer;
  delete this->textureManager;
  delete this->enemyAnimator;
  delete this->hammerAnimator;
  //delete this->currentWindow;
  delete this->levelDrawer;
}

void ViewManager::renderConnectionLostWindow() {
  //Clear the renderer and window
  this->close();
  //Create new renderer and window
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->currentWindow = this->createWindow("Donkey Kong - Connection lost", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             CONNECTION_LOST_WIDTH, CONNECTION_LOST_HEIGHT, 0);

    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) SDL_SetRenderDrawColor(this->renderer, 200, 0, 0, 0);
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
  }

  SDL_RenderClear(this->renderer);

  //Set font color, size and text
  SDL_Color textColor = {255, 0, 0, 0xFF};
  TTF_Font *font = TTF_OpenFont("resources/fonts/font.ttf", 40);
  LTexture errorMessage;
  errorMessage.loadFromRenderedText("Server Disconnected", textColor, font, this->renderer);
  TTF_CloseFont(font);
  //Render window with exit button
  SDL_Event e;
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0 && !quit) {
      quit = e.type == SDL_QUIT;
    }
    errorMessage.render((this->screen_width / 2) - (errorMessage.getWidth() / 2),
                        (this->screen_height / 2) - errorMessage.getHeight());
    SDL_RenderPresent(renderer);
  }

}

ViewManager::ViewManager(const char *title, int xPos, int yPos, int width, int height) {

  this->screen_width = width;
  this->screen_height = height;
  this->hasDefaultConfig = false;
  this->isLobbyView = true;
  this->success = true;

  int flags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->currentWindow = this->createWindow(title, xPos, yPos, width, height, SDL_WINDOW_SHOWN);
    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) this->initializeRendererColor();
    this->initializeTTF();
    this->loadLobbyMedia();
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
    this->success = false;
  }
}

void ViewManager::loadLobbyMedia() {
  this->font = TTF_OpenFont("resources/fonts/font.ttf", 28);

  if (this->font == NULL) {
    printf("Failed to load product sans font! SDL_ttf Error: %s\n", TTF_GetError());
    this->success = false;
  } else {
    //Render the prompt
    SDL_Color textColor = {0, 0, 0, 0xFF};
    if (!this->gPromptInfoTextTexture.loadFromRenderedText("Esperando a que ingresen mas usuarios...", textColor,
                                                           this->font,
                                                           this->renderer)) {
      printf("Failed to render user prompt text!\n");
      this->success = false;
    }
  }
}

void ViewManager::initializeLobbyTextInputs() {
  this->inputUserPosX = (this->screen_width - gPromptUserTextTexture.getWidth()) / 2;
  this->inputUserPosY = 0;
}

void ViewManager::renderWrongCredentialsWindow() {
  //Clear the renderer and window
  this->close();
  //Create new renderer and window
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->currentWindow = this->createWindow("Donkey Kong - Wrong credentials", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             CONNECTION_LOST_WIDTH, CONNECTION_LOST_HEIGHT, 0);
    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) SDL_SetRenderDrawColor(this->renderer, 0, 100, 100, 0);
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
  }

  SDL_RenderClear(this->renderer);

  //Set font color, size and text
  SDL_Color textColor = {255, 0, 0, 0xFF};
  TTF_Font *font = TTF_OpenFont("resources/fonts/font.ttf", 20);
  LTexture errorMessage;
  errorMessage.loadFromRenderedText("Credenciales incorrectas", textColor, font, this->renderer);
  TTF_CloseFont(font);
  //Render window with exit button
  SDL_Event e;
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0 && !quit) {
      quit = e.type == SDL_QUIT;
    }
    errorMessage.render((this->screen_width / 2) - (errorMessage.getWidth() / 2),
                        (this->screen_height / 2) - errorMessage.getHeight());
    SDL_RenderPresent(renderer);
  }
}

void ViewManager::renderClientAlreadyConnectedWindow() {
  //Clear the renderer and window
  this->close();
  //Create new renderer and window
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->currentWindow = this->createWindow("Donkey Kong - User already playing", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             CONNECTION_LOST_WIDTH, CONNECTION_LOST_HEIGHT, 0);

    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) SDL_SetRenderDrawColor(this->renderer, 0, 250, 0, 0);
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
  }

  SDL_RenderClear(this->renderer);

  //Set font color, size and text
  SDL_Color textColor = {255, 0, 0, 0xFF};
  TTF_Font *font = TTF_OpenFont("resources/fonts/font.ttf", 20);
  LTexture errorMessage;
  errorMessage.loadFromRenderedText("Ya se ingreso con este usuario", textColor, font, this->renderer);
  TTF_CloseFont(font);
  //Render window with exit button
  SDL_Event e;
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0 && !quit) {
      quit = e.type == SDL_QUIT;
    }
    errorMessage.render((this->screen_width / 2) - (errorMessage.getWidth() / 2),
                        (this->screen_height / 2) - errorMessage.getHeight());
    SDL_RenderPresent(renderer);
  }
}

void ViewManager::renderUnknownResponseWindow(char connectionResponse) {
  //Clear the renderer and window
  this->close();
  //Create new renderer and window
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->currentWindow = this->createWindow("Donkey Kong - Unknown server connection response", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             CONNECTION_LOST_WIDTH, CONNECTION_LOST_HEIGHT, 0);
    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) SDL_SetRenderDrawColor(this->renderer, 200, 100, 200, 0);
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
  }

  SDL_RenderClear(this->renderer);

  //Set font color, size and text
  SDL_Color textColor = {255, 0, 0, 0xFF};
  TTF_Font *font = TTF_OpenFont("resources/fonts/font.ttf", 20);
  LTexture errorMessage;
  errorMessage.loadFromRenderedText("Respuesta inesperada del servidor" + std::to_string(connectionResponse), textColor,
                                    font, this->renderer);
  TTF_CloseFont(font);
  //Render window with exit button
  SDL_Event e;
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0 && !quit) {
      quit = e.type == SDL_QUIT;
    }
    errorMessage.render((this->screen_width / 2) - (errorMessage.getWidth() / 2),
                        (this->screen_height / 2) - errorMessage.getHeight());
    SDL_RenderPresent(renderer);
  }
}

void ViewManager::renderLobbyIsFullWindow() {
  //Clear the renderer and window
  this->close();
  //Create new renderer and window
  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->currentWindow = this->createWindow("Donkey Kong - Lobby is full", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             CONNECTION_LOST_WIDTH, CONNECTION_LOST_HEIGHT, 0);

    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) SDL_SetRenderDrawColor(this->renderer, 200, 100, 200, 0);
  } else {
    this->showSDLError("SDL could not initialize! SDL Error: %s\n");
  }

  SDL_RenderClear(this->renderer);

  //Set font color, size and text
  SDL_Color textColor = {255, 0, 0, 0xFF};
  TTF_Font *font = TTF_OpenFont("resources/fonts/font.ttf", 20);
  LTexture errorMessage;
  errorMessage.loadFromRenderedText("El lobby esta completo", textColor, font, this->renderer);
  TTF_CloseFont(font);

  //Render window with exit button
  SDL_Event e;
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0 && !quit) {
      quit = e.type == SDL_QUIT;
    }
    errorMessage.render((this->screen_width / 2) - (errorMessage.getWidth() / 2),
                        (this->screen_height / 2) - errorMessage.getHeight());
    SDL_RenderPresent(renderer);
  }
}

