#include "Client.h"

#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(char *port, char *IP) {

  ClientSocket *new_socket = new ClientSocket(port, IP);

  // delete game;
}
