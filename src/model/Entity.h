#ifndef TALLER_PROG_I_2021_1C_KIWI_ENEMY_H
#define TALLER_PROG_I_2021_1C_KIWI_ENEMY_H

#include <SDL_rect.h>
#include "Position.h"

class Entity {

protected:
    Position* pos;
    int velY;
    int velX;
    int distance;
    int direction;
public:
    explicit Entity(Position* pos);

    Entity();

    virtual void update() = 0;

    double getXPosition();

    double getYPosition();

    Position* getPos();

    int getDistance();

    int getDirection();

    bool isGrounded;

  virtual SDL_Rect getRectangle() = 0;

  virtual int getPoints() = 0;

  void kill();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_ENEMY_H
