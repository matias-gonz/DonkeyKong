
#ifndef TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H
#define TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H

#include "../Socket/Socket.h"
#include "../model/Logger.h"

class ClientSocket: public Socket {

public:

  ClientSocket(int port, int IP);

private:
  int socketClient;
  struct sockaddr_in serv_addr;

};

#endif //TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H
