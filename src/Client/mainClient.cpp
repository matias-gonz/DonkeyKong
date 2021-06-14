#include "mainClient.h"
#include "Client.h"


int mainClient(char *IP, char *port) {
  Client *client = new Client(port, IP);

  //TODO change inside if
  if (!client->checkCredentials()) {
    return -1;
  }
  while (client->isRunning()) {
    client->send();
    client->receive();
    client->render();
  }

  return 0;
}