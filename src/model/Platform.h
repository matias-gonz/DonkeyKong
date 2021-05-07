#ifndef TALLER_PROG_I_2021_1C_KIWI_PLATFORM_H
#define TALLER_PROG_I_2021_1C_KIWI_PLATFORM_H
#include "SDL2/SDL_image.h"
#include "Position.h"

#define HEIGHT 576
#define WIDTH 1024

/*typedef struct Position{
    int x;
    int y;
}Position;*/

class Platform {

public:
    Platform(Position position, int count);
    void draw(SDL_Texture* texture);

private:
    Position pos;
    int count;
    SDL_Rect* srcRect;
    SDL_Rect* destRect;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLATFORM_H
