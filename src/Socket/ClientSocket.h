
#ifndef TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H
#define TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H

#include "Socket.h"
#include "../model/Logger.h"

class ClientSocket: public Socket {
public:
    ClientSocket(char *port, char *IP);

  bool isConnected();
  int snd(void *event);
  int receive(void *positions);

private:
  int socketClient;
  struct sockaddr_in serv_addr;
  Socket* socket;
  bool connected;



};

#endif //TALLER_PROG_I_2021_1C_KIWI_CLIENTSOCKET_H
