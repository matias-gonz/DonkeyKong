#ifndef TALLER_PROG_I_2021_1C_KIWI_PRINCESS_H
#define TALLER_PROG_I_2021_1C_KIWI_PRINCESS_H

#include <SDL_rect.h>
#include "Position.h"
#include "Entity.h"

class Princess : public Entity{
private:
    //int movementCounter;
public:
    explicit Princess(Position* pos);
    void update();

  SDL_Rect getRectangle();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PRINCESS_H
