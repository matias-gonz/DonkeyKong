#include <iostream>

#include "mainServer.h"

int mainServer(char **json, char *IP, char *port) {

    Server *server = new Server(port, IP);

    while(server->isRunning()){
        server->listen();
        server->update();
        server->broadcast();
    }

    return 0;
}