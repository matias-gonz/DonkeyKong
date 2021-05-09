#include "viewManager.h"

ViewManager::ViewManager(Game *aGame, const char *title, int xPos, int yPos, int width, int height, bool fullscreen) {
    this->screen_width = width;
    this->screen_height = height;

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
    this->textureManager = new TextureManager(this->renderer);
    this->levelDrawer = new LevelDrawer(this->renderer, this->textureManager);
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
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);

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

LTexture *ViewManager::loadTexture(char *path) {
    LTexture *texture = new LTexture();
    texture->setRenderer(this->getRenderer());

    if (!texture->loadFromFile(path)) {
        printf("Failed to load texture!\n");
    }

    return texture;
}

void ViewManager::drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *destRect) {
    SDL_RenderCopy(renderer, texture, srcRect, destRect);
}

void ViewManager::renderWindow() {
    SDL_RenderClear(renderer);


    //render player
    Player *player = game->getPlayer();
    SDL_Rect dstrect = {static_cast<int>(player->getXPosition()), static_cast<int>(player->getYPosition()), 25, 50};
    SDL_RenderCopy(renderer, this->textureManager->loadPlayerTexture(), NULL, &dstrect);

    //render level
    /*void Platform::draw(SDL_Texture *texture) {
        SDL_Rect* tmpRect = new SDL_Rect();
        tmpRect->x = this->destRect->x;
        tmpRect->y = this->destRect->y;
        tmpRect->h = this->destRect->h;
        tmpRect->w = this->destRect->w;

        for(int i = 0; i < this->count; i++){
            TextureManager::DrawTexture(texture,this->srcRect,tmpRect);
            tmpRect->x += this->destRect->w;
        }

    }

*/

    //Draw level
    levelDrawer->draw(game->getLevel());

    SDL_RenderPresent(renderer);
}