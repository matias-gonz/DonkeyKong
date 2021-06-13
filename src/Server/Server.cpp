#include "Server.h"

pthread_mutex_t mutex;

Server::Server(char *port, char *IP) {
  this->configuration = new Configuration();
  Logger::startLogger(this->configuration, "server.log");
  this->game = new Game(this->configuration);
  this->game->start();
  this->gameController = new GameController(this->game);
  this->eventQueue = cola_crear();
  this->port = port;
  this->ip = IP;
  this->clientCount = 0;
  this->clientMax = 4;
  this->socket = new ServerSocket(port, IP, this->clientMax);
  pthread_mutex_init(&this->mutex, NULL);
  this->sockets = NULL;

}

void *Server::updateThread(void *socket) {
  /*
  auto* s = (ServerSocket*)socket;
  game->addPlayer();
  while(true){
      SDL_Event e;
      s->receive(&e);
      SDL_Event* event = new SDL_Event(e);
      cola_encolar(eventQueue,event);
  }
  */
}

bool Server::isRunning() {
  return this->game->isRunning();
}


void Server::update() {
  /*
  while(true){
      SDL_Event* e = static_cast<SDL_Event *>(cola_desencolar(eventQueue));
      gameController->handleEvents(*e,pthread_self());
      gameController->update();
      plyrPos.playerX = game->getPlayer(pthread_self())->getXPosition();
      plyrPos.playerY = game->getPlayer(pthread_self())->getYPosition();
      delete e;
      broadcast();
  }
   */
}

void Server::broadcast() {
  for (int i = 0; i < this->clientCount; i++) {
    this->socket->snd(&this->plyrPos);
  }

}

void *acceptConnections(void *serv) {
  Server *server = (Server *) serv;
  while (!server->isFull()) {
    server->addNewConnection();
  }

}

void *hndlEvents(void *serv) {
  Server *server = (Server *) serv;
  while (server->isRunning()) {
    server->handleEvents();
  }
}

void Server::start() {
  /*
  pthread_t processComandsT;
  pthread_create(&processComandsT, NULL, reinterpret_cast<void *(*)(void *)>(update), NULL );

  int clientCount = 0;
  pthread_t client1;
  pthread_t client2;
  pthread_t client3;
  pthread_t client4;

  pthread_t clients[4] = {client1,client2,client3,client4};

  while(clientCount < 4){//en vez de while true hacer que loopee solo por la cantiddad maxima de conexiones permitidas
      ServerSocket* newServerSocket = new ServerSocket(port, IP);
      sockets[clientCount] = newServerSocket;
      pthread_create(&clients[clientCount], NULL, updateThread, (void*)newServerSocket);

      clientCount++;

  }
  */
  pthread_t accepterThrd;
  pthread_create(&accepterThrd, NULL, &acceptConnections, this);
  pthread_t eventHandlerThrd;
  pthread_create(&eventHandlerThrd, NULL, &hndlEvents, this);

  pthread_join(accepterThrd, NULL);
}

bool Server::isFull() {
  return (this->clientCount >= this->clientMax);
}

void Server::addNewConnection() {
  if (this->clientCount >= this->clientMax) {
    return;
  }
  int newSocket = this->socket->accept();
  int *tmpSocket = (int *) realloc(this->sockets, (this->clientCount + 1) * sizeof(int));
  if (!tmpSocket) {
    Logger::log(Logger::Error, "Error al reservar memoria. Server::addNewConnection");
    return;
  }
  this->sockets = tmpSocket;
  pthread_mutex_lock(&this->mutex);
  this->sockets[this->clientCount] = newSocket;
  this->clientCount++;
  pthread_mutex_unlock(&this->mutex);
  //printf("Client count = %i\n",this->clientCount);
}

void Server::handleEvents() {
  /*
  SDL_Event* e = static_cast<SDL_Event *>(cola_desencolar(eventQueue));
  if(!e){
      return;
  }
   */
  SDL_Event e;
  if (this->socket->receive(&e) >= 0) {
    this->gameController->handleEvents(e);
  }
  this->gameController->update();
  this->plyrPos.playerX = this->game->getPlayer()->getXPosition();
  this->plyrPos.playerY = this->game->getPlayer()->getYPosition();
  this->broadcast();
}
