#include <iostream>

#include "mainServer.h"

int mainServer(char **json, char *IP, char *port) {

    Server *server = new Server(port, IP);
    server->start();

    return 0;
}