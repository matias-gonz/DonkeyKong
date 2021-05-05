#ifndef TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H

#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>

class ViewManager {
public:
    ViewManager();

    void showSDLError(char *message);

    void setTextureLinear();

    void createWindow();

    SDL_Renderer* getRenderer();

    void createRenderer();

    void initializeRendererColor();

    bool successfulInitialitization();

    void close();

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool success;
    int screen_width = 1280;
    int screen_height = 720;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_VIEWMANAGER_H
