//
// Created by rochi on 14/5/21.
//

#ifndef TALLER_PROG_I_2021_1C_KIWI_BARRELMOVEMENT_H
#define TALLER_PROG_I_2021_1C_KIWI_BARRELMOVEMENT_H

class BarrelMovement{

public:
    BarrelMovement(int direction);
    void update(SDL_Rect *rect);

private:
    int speed;
    int direction;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_BARRELMOVEMENT_H
