#include <unistd.h>
#include "Socket.h"


void Socket::create() {
  //if(!is_valid()) return false;
  if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &this->opt, sizeof(this->opt))) {
    Logger::log(Logger::Error, "Error al crear el setSockOpt");
    throw std::runtime_error("Error al crear el socket");
  }
  this->address.sin_family = AF_INET;
  this->address.sin_addr.s_addr = INADDR_ANY;
}

void Socket::convertToHost(const int port, const char *IP) {
  this->address.sin_port = htons(port);
  int inet_res = inet_pton(AF_INET, IP, &this->address.sin_addr);
  if (inet_res <= 0) {
    Logger::log(Logger::Error, "Error, dirección invalida");
    throw std::runtime_error("Error al convertir las direcciones");
  }
}

void Socket::bind(int port) {
  //if(!is_valid()) return false;

  if (::bind(this->server_fd, (struct sockaddr *) &this->address, sizeof(this->address)) < 0) {
    Logger::log(Logger::Error, "Error al bindear el socket al puerto");
    throw std::runtime_error("Error al bindear el socket al puerto");
  }
}

void Socket::listen(int maxConnections) {
  //if(!is_valid()) return false;
  if (::listen(this->server_fd, maxConnections) < 0) {
    Logger::log(Logger::Error, "Error al escuchar el socket");
    throw std::runtime_error("Error al escuchar el socket");
  }
}

bool Socket::connect() {
  if (::connect(this->server_fd, (struct sockaddr *) &this->address, sizeof(this->address)) < 0) {
    Logger::log(Logger::Error, "Error al establecer conexión con el servidor");
    throw std::runtime_error("Error al conectarse con el servidor");
  } else {
    std::cout << "Se conecto bien" << std::endl;
    return true;
  }
}

int Socket::accept() {
  int new_socket = ::accept(this->server_fd, (struct sockaddr *) &this->address, (socklen_t *) &this->addrlen);
  if (new_socket <= 0) {
    Logger::log(Logger::Error, "Error al aceptar el nuevo socket");
    throw std::runtime_error("Error al aceptar el nuevo socket");
  }
  this->new_socket = new_socket;
  return new_socket;
}

bool Socket::isConnected() {
  return this->connected;
}
