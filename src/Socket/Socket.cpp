#include "Socket.h"

Socket::Socket(char* port,char* IP) {
  // Creating socket file descriptor
  if ((this->server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
    Logger::log(Logger::Error,"Error al crear el socket");
    exit(EXIT_FAILURE);
  }

  this->create();
  this->convertToHost(port, (int) *IP);
  this->bind((int) *port);
  this->Socket::listen();
}

Socket::Socket(char* port,char* IP, int max_connections) {
  // Creating socket file descriptor
  if ((this->server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
    Logger::log(Logger::Error,"Error al crear el socket");
    exit(EXIT_FAILURE);
  }

  this->convertToHost(port, (int) *IP);
  this->connect();
}

void Socket::create() {
  //if(!is_valid()) return false;
  int opt = 1;
  if(setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))== -1){
    Logger::log(Logger::Error,"Error al crear el setSockOpt");
    throw std::runtime_error("Error al crear el socket");
  }
}

void Socket::bind(const int port) {
  //if(!is_valid()) return false;

  this->address.sin_family = AF_INET;
  this->address.sin_addr.s_addr = INADDR_ANY;
  this->address.sin_port = htons(port);
  // Forcefully attaching socket to a port
  if (::bind(this->server_fd, (struct sockaddr *) &this->address, this->addrlen) < 0) {
    Logger::log(Logger::Error,"Error al bindear el socket al puerto");
    throw std::runtime_error("Error al bindear el socket al puerto");
  }
}

void Socket::listen() {
  //if(!is_valid()) return false;
  if (::listen(this->server_fd, 3) < 0) {
    Logger::log(Logger::Error,"Error al escuchar el socket");
    throw std::runtime_error("Error al escuchar el socket");
  }
}

void Socket::convertToHost(const char* IP, const int port) {
  this->address.sin_port = ::htons(port);
  if(::inet_pton(this->address.sin_family, IP,(void*) &this->address.sin_addr) <= 0){
    Logger::log(Logger::Error,"Error, dirección invalida");
    throw std::runtime_error("Error al convertir las direcciones");
  }
}

void Socket::connect() {
  if (::connect(this->server_fd, (struct sockaddr *) &address, addrlen) < 0){
    Logger::log(Logger::Error,"Error al establecer conexión con el servidor");
    throw std::runtime_error("Error al conectarse con el servidor");
  }
}

void Socket::accept() {
  this->new_socket = ::accept(this->server_fd, (struct sockaddr *) &this->address, (socklen_t *) &this->addrlen);
  if(new_socket <= 0){
    Logger::log(Logger::Error,"Error al aceptar el nuevo socket");
    throw std::runtime_error("Error al aceptar el nuevo socket");
  }
}

int Socket::recv(int* dato){
  return 1;
}

int Socket::snd(int* dato){
  return 1;
}