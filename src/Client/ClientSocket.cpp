#include <arpa/inet.h>
#include "ClientSocket.h"

ClientSocket::ClientSocket(char* port,char* IP){
  this->socket = new Socket(port, IP);
}