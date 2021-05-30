#ifndef TALLER_PROG_I_2021_1C_KIWI_TIMEMANAGER_H
#define TALLER_PROG_I_2021_1C_KIWI_TIMEMANAGER_H
#include <chrono>
typedef std::chrono::duration<float> fsec;
typedef std::chrono::system_clock::time_point Time;

class TimeManager {
public:
    TimeManager();
    void sleep();
    void setStartTime();
    void setEndTime();

private:
    Time startTime;
    Time endTime;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_TIMEMANAGER_H
