#include "ServerSocket.h"
#include <arpa/inet.h>

ServerSocket::ServerSocket(char *port, char *IP, int maxConnections) {
  this->opt = 1;

  if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    Logger::log(Logger::Error, "Error al crear el socket");
    exit(EXIT_FAILURE);
  }

  this->create();
  this->convertToHost(atoi(port), IP);
  this->bind(atoi(port));
  this->listen(maxConnections);
}


int ServerSocket::snd(void *positions) {

  int total_bytes_written = 0;
  int bytes_written = 0;
  int send_data_size = sizeof(Positions);
  bool client_socket_still_open = true;

  // Send
  // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
  // sockfd -> file descriptor that refers to a socket
  // buf ->  the message is found in buf.
  // len -> the message and has length len
  // flags
  // The system call send() is used to transmit a message to another socket.
  // The send() call may be used only when the socket is in a connected state (so that the intended recipient is known).

  while ((send_data_size > total_bytes_written) && client_socket_still_open) {
    bytes_written = send(this->new_socket, ((Positions *) positions + total_bytes_written),
                         (send_data_size - total_bytes_written), MSG_NOSIGNAL);
    if (bytes_written < 0) { // Error
      return bytes_written;
    } else if (bytes_written == 0) { // Socket closed
      client_socket_still_open = false;
    } else {
      total_bytes_written += bytes_written;
    }
  }

  return 0;
}

int ServerSocket::receive(void *event) {
  int total_bytes_receive = 0;
  int bytes_receive = 0;
  int receive_data_size = sizeof(SDL_Event);
  bool client_socket_still_open = true;

  while ((receive_data_size > bytes_receive) && client_socket_still_open) {
    bytes_receive = recv(this->new_socket, ((SDL_Event *) event + total_bytes_receive),
                         (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);
    if (bytes_receive < 0) { // Error
      return bytes_receive;
    } else if (bytes_receive == 0) { // Socket closed
      client_socket_still_open = false;
    } else {
      total_bytes_receive += bytes_receive;
    }
  }

  return 0;
}

int ServerSocket::sndString(char *string, int socketNumber) {
  if (::send(socketNumber, string, strlen(string), 0) < 0) {
    char message[50];
    strcat(message, "Error al enviar el string");
    strcat(message, string);
    Logger::log(Logger::Error, message);
    throw std::runtime_error("Error al enviar el string");
  }
  return 0;
}

char *ServerSocket::rcvString(int socketNumber) {
  char string_recieved[20] = {0};
  valread = ::recv(socketNumber, string_recieved, 20, 0);
  return string_recieved;
}

int ServerSocket::receiveCredentials(void *credentials, int socketNumber) {
  int total_bytes_receive = 0;
  int bytes_receive = 0;
  int receive_data_size = sizeof(Credentials);
  bool client_socket_still_open = true;

  while ((receive_data_size > bytes_receive) && client_socket_still_open) {
    bytes_receive = recv(socketNumber, ((Credentials *) credentials + total_bytes_receive),
                         (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);
    if (bytes_receive < 0) { // Error
      return bytes_receive;
    } else if (bytes_receive == 0) { // Socket closed
      client_socket_still_open = false;
    } else {
      total_bytes_receive += bytes_receive;
    }
  }

  return 0;
}
