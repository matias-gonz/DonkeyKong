
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "../Position.h"
#include "../../view/Animator.h"
#include "../Entity.h"
#include "PlayerState.h"

class Player: public Entity {
private:
    int counter;
    bool isClimbing;
    bool canClimb;
    int gravity;
    bool active;
    PlayerState* state;

    static const int VEL = 3;
public:
    explicit Player(Position *pos, char *string);
    ~Player();
    void addLeftVel();

    void addRightVel();

    void jumpUp();

    void resetVelX();

    void update();


    SDL_Rect getRectangle();

    void moveUp(int dy);

    void setGrounded();

    void resetVelY();

    void moveDown(int i);

    int getVelY();

    void resetPos();

    Position *initialPos;

    bool isIn(Position *pPosition);


    void startClimbing(int i);


    void setCanClimb(bool canClimb);


    void stoppedPlaying();

    bool isPlaying();

    char username[20];

    char *getUsername();

    void startedPlaying();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
