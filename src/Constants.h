#ifndef TALLER_PROG_I_2021_1C_KIWI_CONSTANTS_H
#define TALLER_PROG_I_2021_1C_KIWI_CONSTANTS_H

#include "model/Platform.h"
#include "view/ltexture.h"

#define MAX_CLIENTS 4
#define HEIGHT 626
#define WIDTH 1024
#define LOGIN_HEIGHT 300
#define LOGIN_WIDTH 450
#define CONNECTION_LOST_HEIGHT 300
#define CONNECTION_LOST_WIDTH 450
#define TRANSITION_HEIGHT 400
#define TRANSITION_WIDTH 550

enum kindOfAnimation {
  left = -1, up = 0, right = 1, jump = 2
};

struct PlayerTexture {
  int walkWidth = 17;
  int walkHeight = 30;
  int climbWidth = 22;
  int climbHeight = 30;
  int wSeparation = 5;
  int hSeparation = 1;

};

struct BarrelTexture {
    int width = 35;
    int height = 35;
    int wSep = 0;
    int hSep = 1;
};

struct PlatformContainer {
  int count;
  SDL_Rect dest;
};

struct LadderContainer {
  int count;
  SDL_Rect dest;
};

struct FireContainer {
  int count;
  SDL_Rect src;
  SDL_Rect dest;
};

struct EntityContainer {
  int x;
  int y;
  int distance;
  int direction;
};

struct PlayersInformation{
    int x;
    int y;
    int distance;
    int direction;
    bool isActive;
    char username[20];
    int hp;
    int points;
};

struct EventContainer {
  SDL_Event e;
  int clientNum;
};

struct Positions {
  PlatformContainer platforms[71];
  int platformCount;
  LadderContainer ladders[19];
  int ladderCount;
  FireContainer fires[4];
  int fireCount;
  EntityContainer fireEnemies[50];
  int fireEnemyCount;
  PlayersInformation playersInfo[MAX_CLIENTS];
  int playerCount;
  EntityContainer bossInfo;
  EntityContainer princessInfo;
  bool transitioningLevel;
  EntityContainer barrels[10];
  int barrelCount;
  bool endGame;
};

struct Credentials {
  char username[20];
  char password[20];
};

class LTexture;//Forward declaration

struct UsernameBox{
    LTexture box;
    char username[20];
};


#endif //TALLER_PROG_I_2021_1C_KIWI_CONSTANTS_H
