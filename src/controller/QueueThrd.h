#ifndef TALLER_PROG_I_2021_1C_KIWI_QUEUETHRD_H
#define TALLER_PROG_I_2021_1C_KIWI_QUEUETHRD_H
#include<queue>
#include "../Constants.h"

class QueueThrd {
public:
    QueueThrd();

    void push(EventContainer e);
    EventContainer pop();
    bool isEmpty();
private:
    std::queue<EventContainer> queue;
    pthread_mutex_t mutex;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_QUEUETHRD_H
