
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "Position.h"
#include "../view/Animator.h"
#include "Entity.h"

class Player: public Entity {
private:
    int counter;

    static const int VEL = 3;
public:
    explicit Player(Position *pos);
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
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
