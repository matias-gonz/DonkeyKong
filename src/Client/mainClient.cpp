#include "mainClient.h"
#include "Client.h"

int mainClient(char *IP, char *port) {
  Client *client = new Client(port, IP);

  //TODO change inside if
  bool checked = client->checkCredentials();
  while (checked) {
    checked = client->goToLobby();
  }

  while (client->isRunning() && client->gameHasStarted()) {
    client->send();
    client->receive();
    client->render();
  }
  return 0;
}
