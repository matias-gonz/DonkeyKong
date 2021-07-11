
#ifndef TALLER_PROG_I_2021_1C_KIWI_BARRELMOVEMENT_H
#define TALLER_PROG_I_2021_1C_KIWI_BARRELMOVEMENT_H

class BarrelMovement{

public:
    BarrelMovement(int direction);
    void update(SDL_Rect *rect);

    void resetVelY();

    int getDistance();

private:
    int speed;
    int direction;
    int velX;
    int velY;
    int distance;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_BARRELMOVEMENT_H
