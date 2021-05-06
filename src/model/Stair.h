#ifndef TALLER_PROG_I_2021_1C_KIWI_STAIR_H
#define TALLER_PROG_I_2021_1C_KIWI_STAIR_H
#include "SDL2/SDL_image.h"
#include "Position.h"
#include "../view/TextureManager.h"

#define HEIGHT 576
#define WIDTH 1024

class Stair {
public:
    Stair(Position position, int count);
    void draw(SDL_Texture* texture);

private:
    Position pos;
    int count;
    SDL_Rect* srcRect;
    SDL_Rect* destRect;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_STAIR_H
