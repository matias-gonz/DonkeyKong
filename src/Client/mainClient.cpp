#include "mainClient.h"
#include "Client.h"

int mainClient(char *IP, char *port) {
  Client *client = new Client(port, IP);

  if(!client->checkCredentials()){
    Logger::log(Logger::Error, "Credenciales invalidas");
    return 0;
  }
  client->goToLobby();
  client->playMusic();

  while (client->isRunning()) {
    client->send();
    client->receive();
    client->playSounds();
    client->render();
  }
  return 0;
}
