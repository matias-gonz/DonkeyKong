#include "mainClient.h"
#include "Client.h"

int mainClient(char *IP, char *port) {
  Client *client = new Client(port, IP);

  //TODO change inside if
  bool checked = client->checkCredentials();

  while(true){
    char *message = client->rcvString();
    //Check if the server authenticated wrong the user and pass
    bool check = !strcmp(message, " go  to  lobby ");
    if(check){
      client->goToLobby();
      break;
    }
    bool check2 = !strcmp(message, "game completely");
    if (check2) {
      client->startPlaying();
      break;
    }
  }

  while (client->isRunning() && client->gameHasStarted()) {
    client->send();
    client->receive();
    client->render();
  }
  return 0;
}
