#include "Client.h"
#include <netinet/in.h>
#include <arpa/inet.h>
Client::Client(char *port, char *IP) {
    this->configuration = new Configuration();
    Logger::startLogger(this->configuration, "client.txt");


    this->viewManager = new ViewManager(configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

    this->socket = new ClientSocket(port, IP);
    //this->viewManager->renderWindow();//NOse nidea
    SDL_Event event;

    while ( SDL_PollEvent( &event ) != 0 or event.type != SDL_QUIT) {
        cola_t* q = cola_crear();
        cola_encolar(q,&event.type);
        while (SDL_PollEvent( &event ) != 0){
            printf("%d\n",&event.type);
            cola_encolar(q,&event.type);
        }
        this->socket->snd(q);
        cola_destruir(q,NULL);

    }



}

void Client::receive() {
    this->socket->receive(NULL);
}

void Client::send() {
    this->socket->snd((void *) "hola\n");
}
