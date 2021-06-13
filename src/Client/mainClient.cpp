#include "mainClient.h"
#include "Client.h"


int mainClient(char *IP, char *port) {
  //pantalla login
  //manda msg al server y lo autentica

  Client *client = new Client(port, IP);

  //TODO change inside if
  if (!client->checkCredentials()) {
    return -1;
  }
  while (client->isRunning()) {

    //hacer un thread de sends(tendra que ser un while true)
    client->setSended(false);
    client->send();
    //hacer un thread de receives
    client->receive();
    client->render();
  }

  return 0;

}