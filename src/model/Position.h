#ifndef TALLER_PROG_I_2021_1C_KIWI_POSITION_H
#define TALLER_PROG_I_2021_1C_KIWI_POSITION_H


class Position {
private:

    int posX;
    int posY;

public:

    Position();
    Position(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);

    void add(int x, int y);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_POSITION_H
