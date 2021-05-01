#ifndef TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
#define TALLER_PROG_I_2021_1C_KIWI_LEVEL_H

#include<string>
#include"platform.h"

class Level {
private:
    Platform* platforms;
    int count;
    void setPlatforms(string dir);

public:
    Level(string dir);
    Platform* getPlatforms();
    int getCount();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_LEVEL_H
