#include "ServerSocket.h"

ServerSocket::ServerSocket(char* port,char* IP) {
  this->socket = new Socket(port, IP, 3);
}

void ServerSocket::accept(ServerSocket &serverSocket) {
  this->socket->accept();
}

// TO DO CHANGE PARAMETER
void ServerSocket::receive(int *dato) {
  if (!this->socket->recv(dato)) {
    Logger::log(Logger::Error, "Error al leer el dato");
  }
}

void ServerSocket::send(int *dato) {
  if (!this->socket->snd(dato)) {
    Logger::log(Logger::Error, "Error al mandar el dato");
  }
}

ServerSocket::~ServerSocket() {

}
