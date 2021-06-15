#include "ServerSocket.h"
#include <arpa/inet.h>

ServerSocket::ServerSocket(char *port, char *IP,int maxConnections) {
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


int ServerSocket::snd(void *positions, int sckt) {

    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(Positions);
    bool client_socket_still_open = true;

    while ((send_data_size > total_bytes_written) && client_socket_still_open){
        bytes_written = send(sckt, ((Positions*)positions + total_bytes_written), (send_data_size - total_bytes_written), MSG_NOSIGNAL);
        if (bytes_written < 0) { // Error
            return bytes_written;
        }
        else if (bytes_written == 0) { // Socket closed
            client_socket_still_open = false;
        }
        else {
            total_bytes_written += bytes_written;
        }
    }

    return 0;
}

int ServerSocket::receive(void *event, int sckt) {
    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(SDL_Event);
    bool client_socket_still_open = true;

   while ((receive_data_size > bytes_receive) && client_socket_still_open) {
        bytes_receive = recv(sckt, ((SDL_Event *) event + total_bytes_receive),
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

