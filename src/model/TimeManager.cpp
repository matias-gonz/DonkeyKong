#include "TimeManager.h"

#include <unistd.h>

typedef std::chrono::milliseconds ms;
#define FRAMERATE  33

int max(int a, int b){
    return a*(a>=b) + b*(a<b);
}

TimeManager::TimeManager(){

}

void TimeManager::setStartTime() {
    this->startTime = std::chrono::high_resolution_clock::now();
}
void TimeManager::setEndTime() {
    this->endTime = std::chrono::high_resolution_clock::now();
}

void TimeManager::sleep() {
    fsec t = this->endTime - this->startTime;
    int deltaTime = std::chrono::duration_cast<ms>(t).count();
    usleep(usleep(1000*max(FRAMERATE - (deltaTime),0)));
}


