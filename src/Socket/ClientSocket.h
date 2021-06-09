
#ifndef TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H
#define TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H

#include "Socket.h"
#include "../model/Logger.h"

class ClientSocket: public Socket {
public:
    ClientSocket(char *port, char *IP);

    int snd(void *positions);

    int receive(void *event);
};

#endif //TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H
