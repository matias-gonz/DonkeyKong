#include "Server.h"

Server::Server(char *port, char *IP) {

    this->configuration = new Configuration();
    Logger::startLogger(this->configuration, "server.log");
    this->game = new Game(this->configuration);
    this->game->start();
    this->gameController = new GameController(this->game);

    this->socket = new ServerSocket(port, IP);
}

bool Server::isRunning() {
    return this->game->isRunning();
}

void Server::receive() {
    printf("entra al receive\n");
    this->socket->receive(&this->plyrEvent);
    printf("sale del receive\n");
    if (this->plyrEvent.type == SDL_KEYDOWN) {
        printf("KEYDOWN\n");
    } else if (this->plyrEvent.type == SDL_KEYUP) {
        printf("KEYUP\n");
    }

}

void Server::update() {
    printf("pasa al update\n");
    this->gameController->handleEvents(plyrEvent);
    printf("handelio los eventos\n");
    this->gameController->update();
    printf("updatea todo");
    this->plyrPos.playerX = this->game->getPlayer()->getXPosition();
    this->plyrPos.playerY = this->game->getPlayer()->getYPosition();
}

void Server::broadcast() {
    this->socket->snd(&plyrPos);
}
