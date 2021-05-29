#include "ServerSocket.h"

ServerSocket::ServerSocket(int port, int IP) {

  if (!Socket::create()) {
    Logger::log(Logger::Error, "Error al crear el socket");
  }
  if (!Socket::bind(port)) {
    Logger::log(Logger::Error, "Error al bindear el socket al puerto");
  }
  if (!Socket::listen()) {
    Logger::log(Logger::Error, "Error al escuchar el socket");
  }

}

void ServerSocket::accept(ServerSocket &serverSocket) {
  if (!Socket::accept(serverSocket)) {
    Logger::log(Logger::Error, "Error al aceptar el socket");
  }
}

// TO DO CHANGE PARAMETER
void ServerSocket::recieve(int *dato) {
  if (!Socket::recv(dato)) {
    Logger::log(Logger::Error, "Error al leer el dato");
  }
}

void ServerSocket::send(int *dato) {
  if (!Socket::snd(dato)) {
    Logger::log(Logger::Error, "Error al mandar el dato");
  }
}

ServerSocket::~ServerSocket() {

}
