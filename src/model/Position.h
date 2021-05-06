#ifndef TALLER_PROG_I_2021_1C_KIWI_POSITION_H
#define TALLER_PROG_I_2021_1C_KIWI_POSITION_H


class Position {
private:

    double posX;
    double posY;

public:

    Position();
    Position(double x, double y);
    double getX();
    double getY();
    void setX(double x);
    void setY(double y);

    void add(double x, double y);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_POSITION_H
