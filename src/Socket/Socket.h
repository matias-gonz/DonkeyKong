
#ifndef TALLER_PROG_I_2021_1C_KIWI_SOCKET_H
#define TALLER_PROG_I_2021_1C_KIWI_SOCKET_H

#include <netinet/in.h>
#include "../model/Logger.h"


class Socket{

public:

  Socket();

  bool create();

  bool bind(const int port);

  bool listen();

  bool accept(Socket &new_socket);

  int recv(int* dato);

  int snd(int* dato);

private:
  int server_fd;
  int new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  int socketClient;



};

#endif //TALLER_PROG_I_2021_1C_KIWI_SOCKET_H
