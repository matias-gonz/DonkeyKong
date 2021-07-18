
#ifndef TALLER_PROG_I_2021_1C_KIWI_HAMMER_H
#define TALLER_PROG_I_2021_1C_KIWI_HAMMER_H

#include <SDL_rect.h>
#include "Entity.h"
#include "../Constants.h"

class Hammer: public Entity {
public:
  explicit Hammer(Position * position);

  void update();

  SDL_Rect getRectangle();

  void moveUp(int i);

  void resetVelX();
  int getPoints();

private:

  int choseDirection();

  void changeDirection();

};
#endif //TALLER_PROG_I_2021_1C_KIWI_HAMMER_H
