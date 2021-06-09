
#ifndef TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H
#define TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H

#include "../Socket/Socket.h"
#include "../model/Logger.h"

class ClientSocket {

public:

  ClientSocket(char* port,char* IP);

    void send(void *msg);

    void receive(void *msg);

private:
  int socketClient;
  struct sockaddr_in serv_addr;
  Socket* socket;

};

#endif //TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H
