#include "Socket.h"


Socket::Socket() {

  // Creating socket file descriptor
  if ((this->server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
    Logger::log(Logger::Error,"Error al crear el socket");
    exit(EXIT_FAILURE);
  }

}

bool Socket::create() {
  //if(!is_valid()) return false;

  int opt = 1;
  if(setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))== -1){
    Logger::log(Logger::Error,"Error al crear el setSockOpt");
    return false;
  }
  return true;
}

bool Socket::bind(const int port) {
  //if(!is_valid()) return false;

  this->address.sin_family = AF_INET;
  this->address.sin_addr.s_addr = INADDR_ANY;
  this->address.sin_port = htons(port);

  // Forcefully attaching socket to a port
  if (::bind(this->server_fd, (struct sockaddr *) &this->address, this->addrlen) < 0) {
    Logger::log(Logger::Error,"Error al bindear el socket al puerto");
    return false;
  }
  return true;
}
bool Socket::listen() {
  //if(!is_valid()) return false;

  if (::listen(this->server_fd, 3) < 0) {
    Logger::log(Logger::Error,"Error al escuchar el socket");
    return false;
  }
  return true;
}

bool Socket::accept(Socket &new_socket) {
  new_socket.server_fd = ::accept(this->server_fd, (struct sockaddr *) &this->address, (socklen_t *) &this->addrlen);
  if(new_socket.server_fd <= 0){
    Logger::log(Logger::Error,"Error al aceptar el nuevo socket");
    return false;
  }
  return true;
}

int Socket::recv(int* dato){
  return 1;
}
int Socket::snd(int* dato){
  return 1;
}