#include "Server.h"

struct ServerContainer{
    Server* server;
    int clientNum;
    int socketNumber;
};

Server::Server(char *port, char *IP) {
  this->configuration = new Configuration();
  Logger::startLogger(this->configuration, "server.txt");
  this->game = new Game(this->configuration);
  this->gameController = new GameController(this->game);
  this->eventQueue = new QueueThrd();
  this->port = port;
  this->ip = IP;
  this->clientCount = 0;
  this->clientMax =  MAX_CLIENTS;
  this->socket = new ServerSocket(port, IP, this->clientMax);
  pthread_mutex_init(&this->mutex, NULL);
  this->sockets = NULL;
  this->started = false;
  this->gameStarted= false;
}

bool Server::isRunning() {
  return this->game->isRunning();
}


void Server::broadcast() {
  SDL_Delay(25);
  for (int i = 0; i < this->clientCount; i++) {
    this->socket->snd(&this->positions, this->sockets[i]);
  }
}

void Server::broadcastString(char* message) {
  for(int i = 0; i <=this->clientCount; i++){
    this->socket->sndString(message, this->sockets[i]);
  }
}


void *acceptConnections(void *serv) {
  Server *server = (Server *) serv;
  while (!server->isFull()) {
    server->addNewConnection();
  }
  if(server->isFull()){
    char* message = "game completely";
    server->broadcastString(message);
  }
}

void *hndlEvents(void *serv) {
  Server *server = (Server *) serv;
  while (server->isRunning()) {
    server->handleEvents();
  }
}

void* receiveEvents(void * srvr) {
  auto* serverContainer = (ServerContainer*)srvr;
  while(serverContainer->server->isPlayerConnected(serverContainer->clientNum)){
    serverContainer->server->receive(serverContainer->clientNum, serverContainer->socketNumber);
  }
}

void Server::start() {
  pthread_t accepterThrd;
  pthread_create(&accepterThrd, NULL, &acceptConnections, this);

  pthread_exit(NULL);
}
void Server::gameStart(){
  this->game->start();

  pthread_t eventHandlerThrd;
  pthread_create(&eventHandlerThrd, NULL, &hndlEvents, this);
  // No se si poner un exit ( mati )
}

void Server::sendPositions(){
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
  Credentials credentials;
  this->socket->receiveCredentials(&credentials, newSocket);
  std::string username, password_str;
  username.append(credentials.username);
  password_str.append(credentials.password);
  std::cout << username << std::endl;
  if (this->configuration->checkCredentials(&username, &password_str)) {
    /*Aca chequear que este lleno el Lobby y que empice la partida
    if (!this->started) {
      this->started = true;
    }*/
    char *error_msg = "Connection okay";
    this->socket->sndString(error_msg, newSocket);


  } else {
    char *error_msg = "Failed connection";
    this->socket->sndString(error_msg, newSocket);
  }


  int *tmpSocket = (int *) realloc(this->sockets, (this->clientCount + 1) * sizeof(int));
  if (!tmpSocket) {
    Logger::log(Logger::Error, "Error al reservar memoria. Server::addNewConnection");
    return;
  }
  this->sockets = tmpSocket;

  ServerContainer* container = new ServerContainer();
  container->server = this;
  container->clientNum = this->clientCount;
  container->socketNumber = newSocket;

  pthread_mutex_lock(&this->mutex);
  this->game->addPlayer(credentials.username);
  this->sockets[this->clientCount] = newSocket;
  this->clientCount++;

  if(this->clientCount == this->clientMax){
    this->gameStarted= true;
    char* message = "game completely";
    //this->socket->sndString(message, newSocket);
    //this->broadcastString(message);
  }else {
    char* message = "game  not  full";
    //this->socket->sndString(message, newSocket);
    //this->broadcastString(message);
  }

  pthread_mutex_unlock(&this->mutex);

  pthread_t receiveThread;
  pthread_create(&receiveThread, NULL, &receiveEvents, container);
  //printf("Client count = %i\n",this->clientCount);
}

void Server::handleEvents() {
  if (!this->started) return;

  pthread_mutex_lock(&this->mutex);
  bool empty = this->eventQueue->isEmpty();
  pthread_mutex_unlock(&this->mutex);

  if (!empty) {
    pthread_mutex_lock(&this->mutex);
    EventContainer e = this->eventQueue->pop();
    pthread_mutex_unlock(&this->mutex);

    this->gameController->handleEvents(e.e,e.clientNum);

    if(!this->isRunning()) this->quit();

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


void Server::receive(int clientNum, int socketNumber) {
  if (!this->started) return;
  SDL_Event e;
  if(this->socket->receive(&e,socketNumber) < 0){
    return;
  }
  EventContainer event;
  event.e = e;
  event.clientNum = clientNum;
  pthread_mutex_lock(&this->mutex);
  this->eventQueue->push(event);
  pthread_mutex_unlock(&this->mutex);
}


void Server::quit() {
    delete configuration;
    delete game;
    delete gameController;
    delete eventQueue;
    delete socket;

    Logger::log(Logger::Debug, "Servidor cerrado");
    exit(0);
}

bool Server::isPlayerConnected(int playerNumber) {
    return game->isPlayerActive(playerNumber);
}
