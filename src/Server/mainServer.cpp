#include <iostream>

#include "mainServer.h"

int mainServer(char **json, char *IP, char *port) {

    Server *server = new Server(port, IP);
    printf("pasa1\n");
    while(true){

        printf("pasa2\n");

        server->receive();
        printf("pasa3\n");

        server->update();//esto es lo que controla los eventos

        printf("pasa4\n");
        server->broadcast();
    }

    return 0;
}