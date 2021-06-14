#include "Server.h"


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
  auto* server = (Server*)srvr;
  while(server->isRunning()){
    server->receive();
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

  pthread_t receiveThread;
  pthread_create(&receiveThread, NULL, &receiveEvents, this);

  pthread_mutex_lock(&this->mutex);
  this->sockets[this->clientCount] = newSocket;
  this->clientCount++;
  pthread_mutex_unlock(&this->mutex);
  //printf("Client count = %i\n",this->clientCount);
}

void Server::handleEvents() {
  pthread_mutex_lock(&this->mutex);
  bool empty = this->eventQueue->isEmpty();
  pthread_mutex_unlock(&this->mutex);

  if (!empty) {
    pthread_mutex_lock(&this->mutex);
    SDL_Event e = eventQueue->pop();
    printf("popped\n");
    pthread_mutex_unlock(&this->mutex);
    this->gameController->handleEvents(e);
  }
  this->gameController->update();
  this->game->getBossInfo(&this->positions.bossInfo);
  this->game->getPrincessInfo(&this->positions.princessInfo);
  this->game->getPLayerInfo(&this->positions.playerInfo);
  this->game->getPlatforms(this->positions.platforms,&this->positions.platformCount);
  this->game->getLadders(this->positions.ladders,&this->positions.ladderCount);
  this->game->getFires(this->positions.fires,&this->positions.fireCount);
  this->game->getEnemyFiresPos(this->positions.fireEnemies,&this->positions.fireEnemyCount);
  pthread_mutex_lock(&this->mutex);
  this->broadcast();
  pthread_mutex_unlock(&this->mutex);
}




void Server::receive(){
  SDL_Event e;
  if(this->socket->receive(&e) < 0){
    return;
  }
  pthread_mutex_lock(&this->mutex);
  printf("pushed\n");
  this->eventQueue->push(e);
  pthread_mutex_unlock(&this->mutex);
}