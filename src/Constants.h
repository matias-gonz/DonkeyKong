#ifndef TALLER_PROG_I_2021_1C_KIWI_CONSTANTS_H
#define TALLER_PROG_I_2021_1C_KIWI_CONSTANTS_H

#include "model/Platform.h"

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

struct PlatformContainer{
    int count;
    SDL_Rect dest;
};

struct LadderContainer{
    int count;
    SDL_Rect dest;
};
struct FireContainer{
    int count;
    SDL_Rect src;
    SDL_Rect dest;
};

struct FireEnemyContainer{
    int x;
    int y;
    int distance;
    int direction;
};

struct Positions{
    int playerX = 0;
    int playerY = 0;
    PlatformContainer platforms[71];
    int platformCount;
    LadderContainer ladders[19];
    int ladderCount;
    FireContainer fires[4];
    int fireCount;
    FireEnemyContainer fireEnemies[50];
    int fireEnemyCount;
};
#define HEIGHT 576
#define WIDTH 1024
#define LOGIN_HEIGHT 300
#define LOGIN_WIDTH 450


#endif //TALLER_PROG_I_2021_1C_KIWI_CONSTANTS_H