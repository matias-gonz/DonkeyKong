#include <arpa/inet.h>
#include "ClientSocket.h"

ClientSocket::ClientSocket(char* port,char* IP){
  this->socket = new Socket(port, IP);
}

void ClientSocket::send(void *msg) {
    this->socket->snd((char*)msg);
}

void ClientSocket::receive(void *msg) {
    this->socket->recv((int*)msg);
}
