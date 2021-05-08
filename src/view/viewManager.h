#ifndef TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H

#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>
#include "ltexture.h"
#include "../model/Level.h"
#include "../model/Game.h"

class ViewManager {
public:
    ViewManager(Game* );

    SDL_Renderer *getRenderer();

    bool successfulInitialitization();

    void close();

    LTexture* loadTexture(char* path);

    void drawTexture(SDL_Texture *texture, SDL_Rect* srcRect, SDL_Rect* destRect);

    void renderWindow();


private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool success;
    int screen_width = 1280;
    int screen_height = 720;
    Game* game;
    TextureManager* textureManager;

    void setTextureLinear();

    void showSDLError(char *message);

    void createWindow();

    void createRenderer();

    void initializeRendererColor();

};

#endif //TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H
