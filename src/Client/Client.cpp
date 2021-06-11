#include "Client.h"

#include <netinet/in.h>
#include <arpa/inet.h>
Client::Client(char *port, char *IP) {
    this->configuration = new Configuration();
    Logger::startLogger(this->configuration, "client.txt");


    this->viewManager = new ViewManager(configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

    this->socket = new ClientSocket(port, IP);

    SDL_Event event;

    while ( SDL_PollEvent( &event ) != 0 or event.type != SDL_QUIT) {
        while (SDL_PollEvent( &event ) != 0){

        }
    }


}

void Client::receive() {
    this->socket->receive(NULL);
}

void Client::send() {
    this->socket->snd((void *) "hola\n");
}
