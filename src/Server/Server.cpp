#include "Server.h"

struct ServerContainer{
    Server* server;
    int clientNum;
};

Server::Server(char *port, char *IP) {
  this->configuration = new Configuration();
  Logger::startLogger(this->configuration, "server.log");
  this->game = new Game(this->configuration);
  this->game->start();
  this->gameController = new GameController(this->game);
  this->eventQueue = new QueueThrd();
  this->port = port;
  this->ip = IP;
  this->clientCount = 0;
  this->clientMax = 4;
  this->socket = new ServerSocket(port, IP, this->clientMax);
  pthread_mutex_init(&this->mutex, NULL);
  this->sockets = NULL;
  this->_clientsPlaying = false;

}

bool Server::isRunning() {
  return this->game->isRunning();
}


void Server::broadcast() {
  SDL_Delay(25);
  for(int i = 0; i <this->clientCount; i++){
    this->socket->snd(&this->positions, this->sockets[i]);
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

void* receiveEvents(void * srvr) {
  auto* server = (ServerContainer*)srvr;
  while(server->server->isRunning()){
    server->server->receive(server->clientNum);
  }
}

void Server::start() {
  pthread_t accepterThrd;
  pthread_create(&accepterThrd, NULL, &acceptConnections, this);

  pthread_t eventHandlerThrd;
  pthread_create(&eventHandlerThrd, NULL, &hndlEvents, this);

  pthread_exit(NULL);
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

  ServerContainer* container = new ServerContainer();
  container->server = this;
  container->clientNum = this->clientCount;
  pthread_t receiveThread;
  pthread_create(&receiveThread, NULL, &receiveEvents, container);

  pthread_mutex_lock(&this->mutex);
  this->game->addPlayer();
  this->sockets[this->clientCount] = newSocket;
  this->clientCount++;
  pthread_mutex_unlock(&this->mutex);
  //printf("Client count = %i\n",this->clientCount);
}

void Server::handleEvents() {
  if(!this->clientsPlaying()){
    return;
  }
  pthread_mutex_lock(&this->mutex);
  bool empty = this->eventQueue->isEmpty();
  pthread_mutex_unlock(&this->mutex);

  if (!empty) {
    pthread_mutex_lock(&this->mutex);
    EventContainer e = this->eventQueue->pop();
    pthread_mutex_unlock(&this->mutex);
    this->gameController->handleEvents(e.e,e.clientNum);
  }
  this->gameController->update();
  this->game->getBossInfo(&this->positions.bossInfo);
  this->game->getPrincessInfo(&this->positions.princessInfo);
  this->game->getPLayerInfo(this->positions.playersInfo, &this->positions.playerCount);
  this->game->getPlatforms(this->positions.platforms,&this->positions.platformCount);
  this->game->getLadders(this->positions.ladders,&this->positions.ladderCount);
  this->game->getFires(this->positions.fires,&this->positions.fireCount);
  this->game->getEnemyFiresPos(this->positions.fireEnemies,&this->positions.fireEnemyCount);
  pthread_mutex_lock(&this->mutex);
  this->broadcast();
  pthread_mutex_unlock(&this->mutex);
}


void Server::receive(int clientNum) {
  SDL_Event e;
  if(this->socket->receive(&e) < 0){
    return;
  }
  EventContainer event;
  event.e = e;
  event.clientNum = clientNum;
  pthread_mutex_lock(&this->mutex);
  this->eventQueue->push(event);
  pthread_mutex_unlock(&this->mutex);
}

bool Server::clientsPlaying() {
  return (this->game->getPlayerCount() > 0);
}
