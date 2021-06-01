#include "mainClient.h"
#include "Client.h"


int mainClient(char* IP, char* port){

  Client* client = new Client(port, IP);

  return 0;

}