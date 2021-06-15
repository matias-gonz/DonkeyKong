#ifndef TALLER_PROG_I_2021_1C_KIWI_SERVERSOCKET_H
#define TALLER_PROG_I_2021_1C_KIWI_SERVERSOCKET_H

#include "Socket.h"
#include "../model/Logger.h"

class ServerSocket : public Socket {

public:

  ServerSocket(char *port, char *IP, int maxConnections);

  int receive(void *event);

  int snd(void *positions);

  int sndString(char *string, int socketNumber);

  char *rcvString(int socketNumber);

  int receiveCredentials(void *credentials, int socketNumber);

private:
  int socketServer;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_SERVERSOCKET_H
