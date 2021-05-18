#ifndef TALLER_PROG_I_2021_1C_KIWI_PRINCESS_H
#define TALLER_PROG_I_2021_1C_KIWI_PRINCESS_H
#include "Position.h"
#include "Entity.h"

class Princess : public Entity{
private:
    //int movementCounter;
public:
    explicit Princess(Position* pos);
    void update();

};


#endif //TALLER_PROG_I_2021_1C_KIWI_PRINCESS_H
