#ifndef TALLER_PROG_I_2021_1C_KIWI_SOCKET_H
#define TALLER_PROG_I_2021_1C_KIWI_SOCKET_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include "../model/Logger.h"
#include "../Constants.h"

class Socket {

public:

    void create();

    void bind(int port);

    void convertToHost(const int port, const char *IP);

    bool connect();

    void listen(int maxConnections);

    int accept();

    virtual int receive(void* data) = 0;

    virtual int snd(void* data) = 0;

  bool isConnected();

private:
    int socketClient, valread;

    char *message;
  char buffer[1024] = {0};
  bool connected;

protected:
    struct sockaddr_in address;
    int server_fd;
    int opt;
    int new_socket;
    int addrlen = sizeof(address);
};

#endif //TALLER_PROG_I_2021_1C_KIWI_SOCKET_H
