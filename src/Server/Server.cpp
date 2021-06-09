#include "Server.h"

Server::Server(char *port, char *IP) {

  this->configuration = new Configuration();
  Logger::startLogger(this->configuration);
  this->game = new Game(this->configuration);
  this->gameController = new GameController(this->game);

  //ViewManager *viewManager = new ViewManager(game, configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
  //                                          SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

  this->socket = new ServerSocket(port, IP);
}

bool Server::isRunning() {
    return this->game->isRunning();
}

void Server::listen() {
    this->socket->receive(NULL);

}

void Server::update() {
    this->gameController->handleEvents();
    this->gameController->update();
}

void Server::broadcast() {
    this->socket->snd(NULL);
}
