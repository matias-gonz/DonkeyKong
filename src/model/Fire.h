#ifndef TALLER_PROG_I_2021_1C_KIWI_FIRE_H
#define TALLER_PROG_I_2021_1C_KIWI_FIRE_H

#include "Position.h"
#include "SDL2/SDL_image.h"

#define HEIGHT 576
#define WIDTH 1024

class Fire {
public:
    Fire(Position position, int count);
    void draw(SDL_Texture* texture);

    void update();

private:
    Position pos;
    int count;
    SDL_Rect* srcRect;
    SDL_Rect* destRect;

};


#endif //TALLER_PROG_I_2021_1C_KIWI_FIRE_H
