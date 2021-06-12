#include "mainClient.h"
#include "Client.h"


int mainClient(char *IP, char *port) {

    Client *client = new Client(port, IP);

    while (client->isRunning()) {
        //hacer un thread de sends(tendra que ser un while true)
        client->send();
        //hacer un thread de receives
        client->receive();
        client->render();
    }

    return 0;

}