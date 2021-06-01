
#ifndef TALLER_PROG_I_2021_1C_KIWI_SOCKET_H
#define TALLER_PROG_I_2021_1C_KIWI_SOCKET_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include "../model/Logger.h"


class Socket{

public:

  Socket(char* port,char* IP);

  Socket(char* port,char* IP, int max_connections);

  void create();

  void bind(int port);

  void convertToHost(const int port, const char* IP);

  void connect();

  void listen();

  void accept();

  int recv(int* dato);

  int snd(int* dato);

private:
  int server_fd;
  struct sockaddr_in address;
  int new_socket;
  int addrlen = sizeof(address);
  int socketClient;
  int opt;


};

#endif //TALLER_PROG_I_2021_1C_KIWI_SOCKET_H
