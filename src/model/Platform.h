#ifndef TALLER_PROG_I_2021_1C_KIWI_PLATFORM_H
#define TALLER_PROG_I_2021_1C_KIWI_PLATFORM_H
#include "SDL2/SDL_image.h"


typedef struct Position{
    int x;
    int y;
}Position;

class Platform {

public:
    Platform(Position position, int count);
    void draw(SDL_Texture* texture);

private:
    Position pos;
    int count;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLATFORM_H
