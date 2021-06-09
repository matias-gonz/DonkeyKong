#include "Socket.h"

Socket::Socket(char *port, char *IP) {
  // Creating socket file descriptor
  this->opt = 1;
  if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    Logger::log(Logger::Error, "Error al crear el socket");
    exit(EXIT_FAILURE);
  }

  this->address.sin_family = AF_INET;

  this->convertToHost(atoi(port), IP);
  this->connect();
}

Socket::Socket(char *port, char *IP, int max_connections) {
  this->opt = 1;
  // Creating socket file descriptor
  if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    Logger::log(Logger::Error, "Error al crear el socket");
    exit(EXIT_FAILURE);
  }

  this->create();
  this->convertToHost(atoi(port), IP);
  this->bind(atoi(port));
  this->listen();

  if ((this->new_socket = ::accept(this->server_fd, (struct sockaddr *) &this->address, (socklen_t *) &this->addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }
}

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

void Socket::listen() {
  //if(!is_valid()) return false;
  if (::listen(this->server_fd, 3) < 0) {
    Logger::log(Logger::Error, "Error al escuchar el socket");
    throw std::runtime_error("Error al escuchar el socket");
  }
}

void Socket::connect() {
  if (::connect(this->server_fd, (struct sockaddr *) &this->address, sizeof(this->address)) < 0) {
    Logger::log(Logger::Error, "Error al establecer conexión con el servidor");
    throw std::runtime_error("Error al conectarse con el servidor");
  } else {
    std::cout << "Se conecto bien" << std::endl;
  }
}

void Socket::accept() {
    this->new_socket = ::accept(this->server_fd, (struct sockaddr *) &this->address, (socklen_t *) &this->addrlen);
    if (new_socket <= 0) {
        Logger::log(Logger::Error, "Error al aceptar el nuevo socket");
        throw std::runtime_error("Error al aceptar el nuevo socket");
    }
}

int Socket::recv(int *dato) {

    return 1;
}

int Socket::snd(char *dato) {
    

    return 1;
}