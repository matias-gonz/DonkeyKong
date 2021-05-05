#ifndef TALLER_PROG_I_2021_1C_KIWI_TEXTURELOADER_H
#define TALLER_PROG_I_2021_1C_KIWI_TEXTURELOADER_H

#include "SDL2/SDL_image.h"

class TextureLoader {

public:
    static SDL_Texture* loadTexture(const char* file);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_TEXTURELOADER_H
