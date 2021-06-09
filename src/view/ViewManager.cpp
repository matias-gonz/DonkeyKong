#include "ViewManager.h"

//Player
const int LEFTSTARTW = 0;
const int LEFTSTARTH = 0;
const int RIGHTSTARTW = 0;
const int RIGHTSTARTH = 52;
const int SEPARATIONW = 5;
const int texW = 17;
const int texH = 30;

/*ViewManager::ViewManager(Game *aGame, Configuration *configurations, const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {
    this->screen_width = width;
    this->screen_height = height;
    this->configuration = configurations;

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    this->success = true;
    if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
        this->setTextureLinear();
        this->createWindow(title, xPos, yPos, width, height, flags);
        if (this->window != NULL) this->createRenderer();
        if (this->renderer != NULL) this->initializeRendererColor();
    } else {
        this->showSDLError("SDL could not initialize! SDL Error: %s\n");
        this->success = false;
    }

    this->game = aGame;
    this->textureManager = new TextureManager(this->renderer, this->configuration->getSprites());
    this->levelDrawer = new LevelDrawer(this->renderer, this->textureManager);

    SDL_Texture* playerTexture = this->textureManager->getPlayerTexture();
    bool playerTextureSuccess = true;
    if(!playerTexture){
        playerTexture = this->textureManager->getErrorTexture();
        playerTextureSuccess = false;

    }
    SDL_Texture* enemyTexture = this->textureManager->getEnemyTexture();
    bool enemyTextureSuccess = true;
    if(!enemyTexture){
        enemyTexture = this->textureManager->getErrorTexture();
        enemyTextureSuccess = false;
    }

    //this->playerAnimator = new Animator(playerTexture,LEFTSTARTW,LEFTSTARTH,RIGHTSTARTW,RIGHTSTARTH,texW,texH,SEPARATIONW,playerTextureSuccess);
    this->playerAnimator = new PlayerAnimator(playerTexture,success);
    this->enemyAnimator = new Animator(enemyTexture,0,0,0,25,22,24,2,enemyTextureSuccess);

    //ESTOS NO FUNKAN
    //this->bossAnimator = new Animator(this->textureManager->getBossTexture(),0,0,170,0,170,119,0);
    //this->princessAnimator = new Animator(this->textureManager->getPrincessTexture(),4,4,27,4,15,22,0);
}
*/
void ViewManager::showSDLError(char *message) {
    printf(message, SDL_GetError());
}

void ViewManager::setTextureLinear() {
    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }
}

void ViewManager::createWindow(const char *title, int xPos, int yPos, int width, int height, int flags) {
    this->window = SDL_CreateWindow(title, xPos, yPos, this->screen_width,
                                    this->screen_height, flags);
    if (this->window == NULL) {
        this->showSDLError("Window could not be created! SDL Error: %s\n");
        this->success = false;
    }
}

SDL_Renderer *ViewManager::getRenderer() {
    return this->renderer;
}

void ViewManager::createRenderer() {
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (this->renderer == NULL) {
        this->showSDLError("Renderer could not be created! SDL Error: %s\n");
        this->success = false;
    }
}

void ViewManager::initializeRendererColor() {
    //Initialize renderer color
    if( this->configuration->isDefault()) {
      SDL_SetRenderDrawColor(this->renderer, 200, 100, 200, 100);
    }else{
      SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
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

    //Destroy window
    SDL_DestroyRenderer(ViewManager::renderer);
    SDL_DestroyWindow(this->window);
    this->window = NULL;
    ViewManager::renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
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
    Position* playerPos = player->getPos();
    int playerDirection = player->getDirection();
    int playerDistance = player->getDistance();

    //render boss
    Boss* boss = game->getBoss();
    Position* bossPos = boss->getPos();
    //int bossDirection = boss->getDirection();
    //int bossDistance = boss->getDistance();
    SDL_Rect bossDstrect = {bossPos->getX(), bossPos->getY(), 170, 119};;

    //render princess
    Princess* princess = game->getPrincess();
    Position* princessPos = princess->getPos();
    SDL_Rect princessDstrect = {princessPos->getX(), princessPos->getY(), (int)(3*texW), (int)(2*texH)};;
    //int princessDirection = princess->getDirection();
    //int princessDistance = princess->getDistance();


    //this->princessAnimator->draw(this->renderer,princessDirection,princessPos,princessDistance);
    //this->bossAnimator->draw(this->renderer,bossDirection,bossPos,bossDistance);




    //render enemies
    EnemyFire** enemyFires = game->getEnemyFires();
    int enemyFireCount = game->getEnemyFireCount();
    for(int i = 0; i < enemyFireCount; i++){
        Position* enemyPos = enemyFires[i]->getPos();
        int enemyDirection = enemyFires[i]->getDirection();
        int enemyDistance = enemyFires[i]->getDistance();

        this->enemyAnimator->draw(this->renderer,enemyDirection,enemyPos,enemyDistance);
    }

    SDL_RenderCopy(this->renderer, this->textureManager->getBossTexture(), NULL, &bossDstrect);
    SDL_RenderCopy(this->renderer, this->textureManager->getPrincessTexture(), NULL, &princessDstrect);
    this->playerAnimator->draw(this->renderer,playerDirection,playerPos,playerDistance);

    SDL_RenderPresent(renderer);
}

ViewManager::~ViewManager() {
    delete this->playerAnimator;
    delete this->renderer;
    delete this->textureManager;
    delete this->enemyAnimator;
    delete this->window;
    delete this->levelDrawer;
}

ViewManager::ViewManager(Configuration *configurations, char *title, int xPos, int yPos, int width, int height, bool fullscreen) {
    this->screen_width = width;
    this->screen_height = height;
    this->configuration = configurations;

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    this->success = true;
    if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
        this->setTextureLinear();
        this->createWindow(title, xPos, yPos, width, height, flags);
        if (this->window != NULL) this->createRenderer();
        if (this->renderer != NULL) this->initializeRendererColor();
    } else {
        this->showSDLError("SDL could not initialize! SDL Error: %s\n");
        this->success = false;
    }

    this->textureManager = new TextureManager(this->renderer, this->configuration->getSprites());
    this->levelDrawer = new LevelDrawer(this->renderer, this->textureManager);

    SDL_Texture* playerTexture = this->textureManager->getPlayerTexture();
    bool playerTextureSuccess = true;
    if(!playerTexture){
        playerTexture = this->textureManager->getErrorTexture();
        playerTextureSuccess = false;

    }
    SDL_Texture* enemyTexture = this->textureManager->getEnemyTexture();
    bool enemyTextureSuccess = true;
    if(!enemyTexture){
        enemyTexture = this->textureManager->getErrorTexture();
        enemyTextureSuccess = false;
    }

    //this->playerAnimator = new Animator(playerTexture,LEFTSTARTW,LEFTSTARTH,RIGHTSTARTW,RIGHTSTARTH,texW,texH,SEPARATIONW,playerTextureSuccess);
    this->playerAnimator = new PlayerAnimator(playerTexture,success);
    this->enemyAnimator = new Animator(enemyTexture,0,0,0,25,22,24,2,enemyTextureSuccess);

    //ESTOS NO FUNKAN
    //this->bossAnimator = new Animator(this->textureManager->getBossTexture(),0,0,170,0,170,119,0);
    //this->princessAnimator = new Animator(this->textureManager->getPrincessTexture(),4,4,27,4,15,22,0);
}
