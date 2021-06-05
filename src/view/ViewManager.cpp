#include "ViewManager.h"

//Player
const int LEFTSTARTW = 0;
const int LEFTSTARTH = 0;
const int RIGHTSTARTW = 0;
const int RIGHTSTARTH = 52;
const int SEPARATIONW = 5;
const int texW = 17;
const int texH = 30;

ViewManager::ViewManager(Game *aGame, Configuration *configurations, const char *title, int xPos, int yPos, int width,
                         int height, bool fullscreen) {
  this->screen_width = width;
  this->screen_height = height;
  this->configuration = configurations;
  this->hasDefaultConfig = this->configuration->isDefault();
  this->isLoginView = false;

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

  this->game = aGame;
  this->textureManager = new TextureManager(this->renderer, this->configuration->getSprites());
  this->levelDrawer = new LevelDrawer(this->renderer, this->textureManager);

  SDL_Texture *playerTexture = this->textureManager->getPlayerTexture();
  bool playerTextureSuccess = true;
  if (!playerTexture) {
    playerTexture = this->textureManager->getErrorTexture();
    playerTextureSuccess = false;

  }
  SDL_Texture *enemyTexture = this->textureManager->getEnemyTexture();
  bool enemyTextureSuccess = true;
  if (!enemyTexture) {
    enemyTexture = this->textureManager->getErrorTexture();
    enemyTextureSuccess = false;
  }

  //this->playerAnimator = new Animator(playerTexture,LEFTSTARTW,LEFTSTARTH,RIGHTSTARTW,RIGHTSTARTH,texW,texH,SEPARATIONW,playerTextureSuccess);
  this->playerAnimator = new PlayerAnimator(playerTexture, success);
  this->enemyAnimator = new Animator(enemyTexture, 0, 0, 0, 25, 22, 24, 2, enemyTextureSuccess);

  //ESTOS NO FUNKAN
  //this->bossAnimator = new Animator(this->textureManager->getBossTexture(),0,0,170,0,170,119,0);
  //this->princessAnimator = new Animator(this->textureManager->getPrincessTexture(),4,4,27,4,15,22,0);
}

ViewManager::ViewManager(const char *title, int xPos, int yPos, int width, int height) {

  this->screen_width = width;
  this->screen_height = height;
  this->hasDefaultConfig = false;
  this->isLoginView = true;
  this->success = true;

  int flags = 0;


  if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
    this->setTextureLinear();
    this->currentWindow = this->createWindow(title, xPos, yPos, width, height, SDL_WINDOW_SHOWN);
    if (this->currentWindow != NULL) this->createRenderer();
    if (this->renderer != NULL) this->initializeRendererColor();
    this->initializeTTF();
    this->loadMedia();
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
  this->renderer = SDL_CreateRenderer(this->currentWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
  if(this->isLoginView){
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

void ViewManager::close(bool* quit) {

  SDL_Event event;      //Event handler

  while(event.type != SDL_QUIT){
    while(SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT){
        *quit = true;
        SDL_Quit();
        exit(1);
      }
      SDL_RenderPresent(renderer);
      // to simulate OP's flashingText()
      SDL_Delay(50);
    }
    SDL_Delay(100);
  }

  /*
   * //Destroy window
  SDL_DestroyRenderer(ViewManager::renderer);
  SDL_DestroyWindow(this->currentWindow);
  this->currentWindow = NULL;
  ViewManager::renderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
   */
}

void ViewManager::drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect) {
  SDL_RenderCopy(renderer, texture, srcRect, destRect);
}

void ViewManager::renderWindow() {
  SDL_RenderClear(this->renderer);

  //Draw level
  levelDrawer->draw(game->getLevel());

  //render player
  Player *player = game->getPlayer();
  Position *playerPos = player->getPos();
  int playerDirection = player->getDirection();
  int playerDistance = player->getDistance();

  //render boss
  Boss *boss = game->getBoss();
  Position *bossPos = boss->getPos();
  //int bossDirection = boss->getDirection();
  //int bossDistance = boss->getDistance();
  SDL_Rect bossDstrect = {bossPos->getX(), bossPos->getY(), 170, 119};;

  //render princess
  Princess *princess = game->getPrincess();
  Position *princessPos = princess->getPos();
  SDL_Rect princessDstrect = {princessPos->getX(), princessPos->getY(), (int) (3 * texW), (int) (2 * texH)};;
  //int princessDirection = princess->getDirection();
  //int princessDistance = princess->getDistance();


  //this->princessAnimator->draw(this->renderer,princessDirection,princessPos,princessDistance);
  //this->bossAnimator->draw(this->renderer,bossDirection,bossPos,bossDistance);

  //render enemies
  EnemyFire **enemyFires = game->getEnemyFires();
  int enemyFireCount = game->getEnemyFireCount();
  for (int i = 0; i < enemyFireCount; i++) {
    Position *enemyPos = enemyFires[i]->getPos();
    int enemyDirection = enemyFires[i]->getDirection();
    int enemyDistance = enemyFires[i]->getDistance();

    this->enemyAnimator->draw(this->renderer, enemyDirection, enemyPos, enemyDistance);
  }

  SDL_RenderCopy(this->renderer, this->textureManager->getBossTexture(), NULL, &bossDstrect);
  SDL_RenderCopy(this->renderer, this->textureManager->getPrincessTexture(), NULL, &princessDstrect);
  this->playerAnimator->draw(this->renderer, playerDirection, playerPos, playerDistance);

  SDL_RenderPresent(renderer);
}

void ViewManager::renderLoginWindow(){

  if(this->success){
    //Main loop flag
    bool quit = false;
    SDL_Event e;
    SDL_Color textColor = { 0, 0, 0, 0xFF };
    std::string inputTextUser = "Ingrese usuario";
    std::string inputTextPass = "Ingrese password";
    gInputUserTextTexture.loadFromRenderedText(inputTextUser.c_str(), textColor, this->font, this->renderer );
    gInputPasswordTextTexture.loadFromRenderedText(inputTextPass.c_str(), textColor, this->font, this->renderer );
    SDL_StartTextInput();

    while( !quit ){
      bool renderText = false;
      //this->close(& quit);
      while(SDL_PollEvent( &e ) != 0){
        //User requests quit
        if( e.type == SDL_QUIT )
        {
          quit = true;
        }
          //Special key input
        else if( e.type == SDL_KEYDOWN ){
          if( e.key.keysym.sym == SDLK_BACKSPACE && inputTextUser.length() > 0 )
          {
            inputTextUser.pop_back();
            renderText = true;
          }else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ){
            SDL_SetClipboardText(inputTextUser.c_str() );
          }else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ){
            inputTextUser = SDL_GetClipboardText();
            renderText = true;
          }
        }else if( e.type == SDL_TEXTINPUT ){
          if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) ){
            inputTextUser += e.text.text;
            renderText = true;
          }
        }
      }
      if( renderText ){
        if(inputTextUser != "" &&  inputTextPass != ""){
          gInputUserTextTexture.loadFromRenderedText(inputTextUser.c_str(), textColor, this->font, this->renderer );
          gInputPasswordTextTexture.loadFromRenderedText(inputTextPass.c_str(), textColor, this->font, this->renderer );
        }else{
          gInputUserTextTexture.loadFromRenderedText(" ", textColor, this->font, this->renderer );
          gInputPasswordTextTexture.loadFromRenderedText(" ", textColor, this->font, this->renderer );
        }
      }
      SDL_RenderClear(this->renderer);
      gPromptUserTextTexture.render((this->screen_width - gPromptUserTextTexture.getWidth() ) / 2, 0 );
      gInputUserTextTexture.render((this->screen_width - gInputUserTextTexture.getWidth() ) / 2, gPromptUserTextTexture.getHeight() );
      gPromptPasswordTextTexture.render((this->screen_width - gPromptPasswordTextTexture.getWidth() ) / 2, 100 );
      gInputPasswordTextTexture.render((this->screen_width - gInputPasswordTextTexture.getWidth() ) / 2, 100 + gInputPasswordTextTexture.getHeight() );

      //Update screen
      SDL_RenderPresent( this->renderer);
    }

    //Disable text input
    SDL_StopTextInput();
  }
}

void ViewManager::initializeTTF(){
  //Initialize SDL_ttf
  if( TTF_Init() == -1 ){
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    this->success = false;
  }
}

void ViewManager::loadMedia(){

  //Open the font
  this->font = TTF_OpenFont( "resources/fonts/lazy.ttf", 28 );

  if( this->font == NULL ){
    printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    this->success = false;
  }else{
    //Render the prompt
    SDL_Color textColor = { 0, 0, 0, 0xFF };
    if( !this->gPromptUserTextTexture.loadFromRenderedText("Ingrese usuario:", textColor, this->font, this->renderer) && (!this->gPromptPasswordTextTexture.loadFromRenderedText("Ingrese contrase;a:", textColor, this->font, this->renderer))){
      printf( "Failed to render prompt text!\n" );
      this->success = false;
    }
  }

}

ViewManager::~ViewManager() {
  delete this->playerAnimator;
  delete this->renderer;
  delete this->textureManager;
  delete this->enemyAnimator;
  delete this->currentWindow;
  delete this->levelDrawer;
}