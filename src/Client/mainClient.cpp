#include "mainClient.h"
#include "Client.h"


int mainClient(char* IP, char* port){

  Client* client = new Client(port, IP);

  while(true){
      client->send();
      client->receive();
      //client->render();
  }

  return 0;

}