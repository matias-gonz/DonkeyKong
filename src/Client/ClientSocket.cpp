#include <arpa/inet.h>
#include "ClientSocket.h"

ClientSocket::ClientSocket(int port, int IP){

  if (!Socket::create()) {
    Logger::log(Logger::Error, "Error al crear el socket");
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);


// TO DO MOVE TO SOCKET.CPP

  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, reinterpret_cast<const char *>(IP), &serv_addr.sin_addr) <= 0){
    Logger::log(Logger::Error,"Error, direccion no soportada");
    exit(-1);
  }

  if (connect(socketClient, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    Logger::log(Logger::Error,"Error conexion fallida con el servidor");
    exit(-1);
  }

}