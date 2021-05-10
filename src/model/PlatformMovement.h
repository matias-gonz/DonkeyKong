#ifndef TALLER_PROG_I_2021_1C_KIWI_PLATFORMMOVEMENT_H
#define TALLER_PROG_I_2021_1C_KIWI_PLATFORMMOVEMENT_H


class PlatformMovement {

public:
    PlatformMovement(bool b);

    void update(SDL_Rect *rect);

private:
    bool isMoving;
    int speed;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLATFORMMOVEMENT_H
