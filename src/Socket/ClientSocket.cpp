#include "ClientSocket.h"
#include <arpa/inet.h>

ClientSocket::ClientSocket(char *port, char *IP){
    // Creating socket file descriptor
    this->opt = 1;
    if ((this->server_fd = ::socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        Logger::log(Logger::Error, "Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    this->address.sin_family = AF_INET;

    this->convertToHost(atoi(port), IP);
    this->connected = this->connect();
}


int ClientSocket::receive(void *positions) {
    //printf("receive started\n");
    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(Positions);
    bool client_socket_still_open = true;

    while ((receive_data_size > bytes_receive) && client_socket_still_open) {
        bytes_receive = recv(this->server_fd, ((Positions*) positions+ total_bytes_receive), (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);

        if (bytes_receive < 0) { // Error
            return bytes_receive;
        }
        else if (bytes_receive == 0) { // Socket closed
            client_socket_still_open = false;
        }
        else {
            total_bytes_receive += bytes_receive;
        }
    }
    //printf("receive finished\n");
    return 0;
}

int ClientSocket::snd(void *event) {
  int total_bytes_written = 0;
  int bytes_written = 0;
  int send_data_size = sizeof(SDL_Event);
  bool client_socket_still_open = true;

  while ((send_data_size > total_bytes_written) && client_socket_still_open) {
    bytes_written = send(this->server_fd, ((SDL_Event *) event + total_bytes_written),
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

bool ClientSocket::isConnected(){
  return this->connected;
}

int ClientSocket::sndString(char* string, int socketNumber) {
  if (::send(this->server_fd, string, strlen(string),0) < 0) {
    char message[50];
    strcat(message,"Error al enviar el string");
    strcat(message,string);
    Logger::log(Logger::Error, message);
    throw std::runtime_error("Error al enviar el string");
  }
  return 0;
}

int ClientSocket::sndCredentials(void *credentials) {
  int total_bytes_written = 0;
  int bytes_written = 0;
  int send_data_size = sizeof(Credentials);
  bool client_socket_still_open = true;

  while ((send_data_size > total_bytes_written) && client_socket_still_open) {
    bytes_written = send(this->server_fd, ((Credentials *) credentials + total_bytes_written),
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

char* ClientSocket::rcvString(int socketNumber) {
  valread = ::recv(this->server_fd , buffer, 1024, 0);
  return buffer;
}
