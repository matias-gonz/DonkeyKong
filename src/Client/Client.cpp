#include "Client.h"
#include <netinet/in.h>
#include <arpa/inet.h>
Client::Client(char *port, char *IP) {
    this->running = true;
    this->configuration = new Configuration();
    Logger::startLogger(this->configuration, "client.txt");


    this->viewManager = new ViewManager(configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

    this->socket = new ClientSocket(port, IP);

}
void Client::receive() {
    if(!this->sended){return;}
    this->socket->receive(&playerPositions);
}

void Client::send() {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT){
            this->running = false;
            return;
        }
        if(this->eventIsValid(event)){
            this->sended = true;
            this->socket->snd(&event);
        }

    }
}
bool Client::eventIsValid(SDL_Event event){
    return (event.type == SDL_KEYDOWN or event.type == SDL_KEYUP);
}

bool Client::isRunning() {
    return this->running;
}

void Client::render() {
    viewManager->renderWindow(this->playerPositions);
}

void Client::setSended(bool b) {
    this->sended = b;
}
