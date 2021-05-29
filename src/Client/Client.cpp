#include "Client.h"

#include <netinet/in.h>
#include <arpa/inet.h>

Client:: Client(char **port, char **IP){

  ClientSocket* new_socket = new ClientSocket( (int) **port, (int) **IP );


  int socketClient = 0;
  struct sockaddr_in serv_addr;


  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons((int)**port);


}