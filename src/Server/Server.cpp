#include "Server.h"

Server::Server(char *port, char *IP) {
  this->configuration = new Configuration();
  Logger::startLogger(this->configuration, "server.txt");
  this->game = new Game(this->configuration);
  this->gameController = new GameController(this->game);
  this->eventQueue = new QueueThrd();
  this->port = port;
  this->ip = IP;
  this->totalClientsCount = 0;
  this->onlineClientsCount = 0;
  this->offlineClientsCount = 0;
  this->clientMax = 4;
  this->socket = new ServerSocket(port, IP, this->clientMax);
  pthread_mutex_init(&this->mutex, NULL);
  this->sockets = NULL;
  this->_clientsPlaying = false;
  this->started = false;
  this->game->start();
}

bool Server::isRunning() {
  return this->game->isRunning();
}


void Server::broadcast() {
  SDL_Delay(25);
  for(int i = 0; i <this->totalClientsCount; i++){
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
  auto* serverContainer = (ServerContainer*)srvr;
  while(serverContainer->server->isPlayerConnected(serverContainer->clientNum)){
    serverContainer->server->receive(serverContainer->clientNum, serverContainer->socketNumber);
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
  return (this->totalClientsCount >= this->clientMax);
}

void Server::addNewConnection() {
  if (this->totalClientsCount >= this->clientMax) {
    return;
  }
  //Create socket
  int newSocket = this->socket->accept();

  //Read credentials
  Credentials credentials;
  this->socket->receiveCredentials(&credentials, newSocket);
  std::string username, password_str;
  username.append(credentials.username);
  password_str.append(credentials.password);

  //Case there are offline players, try to reconnect
  bool hasReconnected = false;
  if(this->offlineClientsCount > 0)
     hasReconnected = this->tryToReconnectUsing(credentials, newSocket);

  //Case new client
  //configuration->checkCredentials(&username, &password_str)
  if (!hasReconnected && !this->clientIsOnline(credentials)){
    this->addNewClient(credentials, newSocket);
    char *error_msg = "Connection okay";
    this->socket->sndString(error_msg, newSocket);

  } else {
    char *error_msg = "Failed connection";
    this->socket->sndString(error_msg, newSocket);
  }
}

void Server::handleEvents() {
  if (!this->started) return;

  pthread_mutex_lock(&this->mutex);
  bool empty = this->eventQueue->isEmpty();
  pthread_mutex_unlock(&this->mutex);

  if (!empty) {
    pthread_mutex_lock(&this->mutex);
    EventContainer eventContainer = this->eventQueue->pop();
    pthread_mutex_unlock(&this->mutex);

    this->gameController->handleEvents(eventContainer.e, eventContainer.clientNum);
    //Check if the client has desconnected
    if (eventContainer.e.type == SDL_QUIT)
      this->clientSetToOffline(eventContainer.clientNum);
    //Check if the game is still running after handling the events
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

bool Server::clientsPlaying() {
  return (this->game->getPlayerCount() > 0);
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

void Server::addNewClient(Credentials credentials, int newSocket) {

  //If it is the first client start the game
  if (!this->started) {
    this->started = true;
  }

  //Allocate memory for a new socket
  int *tmpSocket = (int *) realloc(this->sockets, (this->totalClientsCount + 1) * sizeof(int));
  if (!tmpSocket) {
    Logger::log(Logger::Error, "Error al reservar memoria. Server::addNewConnection");
    return;
  }
  this->sockets = tmpSocket;

  //Create new ServerContainer(playerConnection)
  ServerContainer* container = new ServerContainer();
  container->server = this;
  container->clientNum = this->totalClientsCount;
  container->socketNumber = newSocket;
  container->username.append(credentials.username);
  container->password.append(credentials.password);
  container->isOnline = true;

  //Add the player, the socket and the container to their arrays
  pthread_mutex_lock(&this->mutex);
  this->game->addPlayer(credentials.username);
  this->sockets[this->totalClientsCount] = newSocket;
  this->clientConnections.push_back(container);
  this->totalClientsCount++;
  this->onlineClientsCount++;
  pthread_mutex_unlock(&this->mutex);

  //Create the thread to receive
  pthread_t receiveThread;
  pthread_create(&receiveThread, NULL, &receiveEvents, container);
}

bool Server::tryToReconnectUsing(Credentials credentials, int newSocket) {
  bool hasReconnected = false;
  bool foundClient = false;
  int clientNumberToReconnect = 0;

  //Search for the old connection
  while(!hasReconnected && !foundClient){
    foundClient = (this->clientConnections[clientNumberToReconnect]->username == credentials.username) &&
            (this->clientConnections[clientNumberToReconnect]->password == credentials.password);
    //If found and is offline recconect it
    if(foundClient && !clientConnections[clientNumberToReconnect]->isOnline){
      hasReconnected = true;
      this->reconnectClient(clientNumberToReconnect,newSocket);
    }

    clientNumberToReconnect++;
  }

  return hasReconnected;
}

bool Server::clientIsOnline(Credentials credentials) {
  return false;
}

void Server::reconnectClient(int clientNumberToReconnect, int newSocket) {
  ServerContainer *clientToReconnect = clientConnections[clientNumberToReconnect];
  //Replace the old socket for the new one and client is back online
  clientToReconnect->socketNumber = newSocket;
  clientToReconnect->isOnline = true;

  //Replace the old socket for the new one and client is back online
  pthread_mutex_lock(&this->mutex);
  this->sockets[clientNumberToReconnect] = newSocket;
  this->onlineClientsCount++;
  this->offlineClientsCount--;

  //Player is active again (cambiar despues rompe encapsulamiento)
  this->game->getPlayer(clientNumberToReconnect)->startedPlaying();
  pthread_mutex_unlock(&this->mutex);

  //Create the thread to receive
  pthread_t receiveThread;
  pthread_create(&receiveThread, NULL, &receiveEvents, clientToReconnect);
  Logger::log(Logger::Debug, "se reconecto",clientNumberToReconnect);
}

void Server::clientSetToOffline(int clientNumber) {

  pthread_mutex_lock(&this->mutex);
  clientConnections[clientNumber]->isOnline = false;

  this->onlineClientsCount--;
  this->offlineClientsCount++;
  pthread_mutex_unlock(&this->mutex);

  Logger::log(Logger::Info, "se desconecto",clientNumber);

}
