#include <iostream>

#include "mainServer.h"

int mainServer( char** json, char** IP, char** port) {

  Server* server = new Server(port, IP);

    return 0;
}