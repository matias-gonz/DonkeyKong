#ifndef TALLER_PROG_I_2021_1C_KIWI_PLATFORMMOVEMENT_H
#define TALLER_PROG_I_2021_1C_KIWI_PLATFORMMOVEMENT_H


class PlatformMovement {

public:
    PlatformMovement(int direction);

    void update(SDL_Rect *rect);

private:
    int direction;
    int speed;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLATFORMMOVEMENT_H
