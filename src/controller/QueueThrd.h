#ifndef TALLER_PROG_I_2021_1C_KIWI_QUEUETHRD_H
#define TALLER_PROG_I_2021_1C_KIWI_QUEUETHRD_H
#include<queue>

class QueueThrd {
public:
    QueueThrd();

    void push(SDL_Event e);
    SDL_Event pop();
    bool isEmpty();
private:
    std::queue<SDL_Event*> queue;
    pthread_mutex_t mutex;
};


#endif //TALLER_PROG_I_2021_1C_KIWI_QUEUETHRD_H
