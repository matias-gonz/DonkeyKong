#ifndef TALLER_PROG_I_2021_1C_KIWI_SERVERSOCKET_H
#define TALLER_PROG_I_2021_1C_KIWI_SERVERSOCKET_H

#include "../Socket/Socket.h"
#include "../model/Logger.h"

class ServerSocket: public Socket {

public:

  ServerSocket(int port, int IP);

  ServerSocket();

  void accept(ServerSocket &serverSocket);

  void recieve(int* dato);

  void send(int* dato);

  ~ServerSocket();


};

#endif //TALLER_PROG_I_2021_1C_KIWI_SERVERSOCKET_H
