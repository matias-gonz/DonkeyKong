#ifndef TALLER_PROG_I_2021_1C_KIWI_ENEMY_H
#define TALLER_PROG_I_2021_1C_KIWI_ENEMY_H

#include "Position.h"

class Entity {

protected:
    bool isGrounded;
    Position* pos;
    int velY;
    int velX;
    int distance;
    int kindOfAnimation;
public:
    Entity(Position* pos);

    virtual void update();

    double getXPosition();

    double getYPosition();

    Position* getPos();

    int getDistance();

    int getDirection();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_ENEMY_H
