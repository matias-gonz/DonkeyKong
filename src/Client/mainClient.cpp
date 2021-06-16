#include "mainClient.h"
#include "Client.h"

int mainClient(char *IP, char *port) {
  Client *client = new Client(port, IP);

  if(!client->checkCredentials()){
    Logger::log(Logger::Error, "Credenciales invalidas");
    return -1;
  }
  client->goToLobby();

  while (client->isRunning()) {
    client->send();
    client->receive();
    client->render();
  }
  return 0;
}
