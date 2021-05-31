#ifndef TALLER_PROG_I_2021_1C_KIWI_CONSTANTS_H
#define TALLER_PROG_I_2021_1C_KIWI_CONSTANTS_H

enum kindOfAnimation {
    left = -1, up = 0,right = 1, jump = 2
};

struct PlayerTexture{
    int walkWidth = 17;
    int walkHeight = 30;
    int climbWidth = 22;
    int climbHeight = 30;
    int wSeparation = 5;
    int hSeparation = 1;

};
PlayerTexture plyrTex;

#define HEIGHT 576
#define WIDTH 1024


#endif //TALLER_PROG_I_2021_1C_KIWI_CONSTANTS_H
