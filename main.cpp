#include <getopt.h>
#include <cstdio>
#include "src/Server/mainServer.h"
#include "src/Client/mainClient.h"

#define NULL 0;

bool checkArgs(int argc, char *args[], char **input, char **IP, char **port) {

  const char *short_opt = "scj:i:p:";
  int c;
  bool isServer = false;

  struct option long_opt[] = {
      {"server", no_argument,       0, 's'},
      {"client", no_argument,       0, 'c'},
      {"json",   required_argument, 0, 'j'},
      {"IP",     required_argument, 0, 'i'},
      {"port",   required_argument, 0, 'p'},
      {0, 0,                        0, 0}
  };

  while ((c = getopt_long(argc, args, short_opt, long_opt, 0)) != -1) {
    switch (c) {
      case 's':
        isServer = true;
        break;
      case 'c':
        isServer = false;
        break;
      case 'j':
        *input = optarg;
        break;
      case 'i':
        *IP = optarg;
        break;
      case 'p':
        *port = optarg;
        break;
      default:
        printf("%s: invalid option -- %c\n", args[0]);
    }
  }

  return isServer;
}

int main(int argc, char *args[]) {

  char *json;
  char *IP;
  char *port;
  bool isServer = checkArgs(argc, args, &json, &IP, &port);
  if (isServer) {
    return mainServer(&json, IP, port);
  } else {
    return mainClient(IP, port);
  }
}
