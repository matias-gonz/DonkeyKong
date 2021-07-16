#include "Server.h"

Server::Server(char *port, char *IP) {
  this->configuration = new Configuration();
  Logger::startLogger(this->configuration, "server.txt");
  char messageIP[100] = {0};
  strcat(messageIP, "IP del servidor: ");
  strcat(messageIP, IP);
  Logger::log(Logger::Info, messageIP);
  char messagePort[100] = {0};
  strcat(messagePort, "Puerto del servidor: ");
  strcat(messagePort, port);
  Logger::log(Logger::Info, messagePort);

  this->game = new Game(this->configuration);
  this->gameController = new GameController(this->game);
  this->eventQueue = new QueueThrd();
  this->port = port;
  this->ip = IP;
  this->totalClientsCount = 0;
  this->onlineClientsCount = 0;
  this->offlineClientsCount = 0;
  this->clientMax = this->configuration->getClientMax();
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
  for (int i = 0; i < this->totalClientsCount; i++) {
    this->socket->snd(&this->positions, this->sockets[i]);
  }

}

void *acceptConnections(void *serv) {
  Server *server = (Server *) serv;
  while (!server->hasAllClientsOnline()) {
    server->addNewConnection();
  }
  server->broadcastGameStart();

  while (server->hasAllClientsOnline()) {
    server->rejectConnection();
  }

}

void *reacceptConnections(void *serv) {
  Server *server = (Server *) serv;
  while (!server->hasAllClientsOnline()) {
    server->addNewConnection();
  }
}

void *hndlEvents(void *serv) {
  Server *server = (Server *) serv;
  while (server->isRunning()) {
    server->handleEvents();
  }
}

void *receiveEvents(void *srvr) {
  auto *serverContainer = (ServerContainer *) srvr;
  while (serverContainer->server->isPlayerConnected(serverContainer->clientNum)) {
    serverContainer->server->receive(serverContainer->clientNum, serverContainer->socketNumber);
  }
  pthread_join(pthread_self(), NULL);
}

void Server::start() {
  Logger::log(Logger::Info, "Se lanza accepter thread");
  pthread_t accepterThrd;
  pthread_create(&accepterThrd, NULL, &acceptConnections, this);

  Logger::log(Logger::Info, "Se lanza eventHandler thread");
  pthread_t eventHandlerThrd;
  pthread_create(&eventHandlerThrd, NULL, &hndlEvents, this);

  pthread_join(eventHandlerThrd, NULL);
}

bool Server::hasAllClientsOnline() {
  return (this->onlineClientsCount >= this->clientMax);
}

void Server::addNewConnection() {
  pthread_mutex_lock(&this->mutex);
  Logger::log(Logger::Info, "Esperando accept");
  pthread_mutex_unlock(&this->mutex);
  //Create socket
  int newSocket = this->socket->accept();
  char playerCount = this->game->getPlayerCount();
  this->socket->sndChar(&playerCount, newSocket);
  //enviar al cliente el game->playerCount
  pthread_mutex_lock(&this->mutex);
  Logger::log(Logger::Info, "Se acepta nueva conexion con socket");
  pthread_mutex_unlock(&this->mutex);

  //Read credentials
  Credentials credentials;
  this->socket->receiveCredentials(&credentials, newSocket);
  std::string username, password_str;
  username.append(credentials.username);
  password_str.append(credentials.password);

  //Case client already online
  if (this->clientIsOnline(credentials)) {

    char o = 'a';
    this->socket->sndChar(&o, newSocket);
    return;

  }

  //Case there are offline players, try to reconnect
  bool hasReconnected = false;
  if (this->offlineClientsCount > 0)
    hasReconnected = this->tryToReconnectUsing(credentials, newSocket);

  //Case lobby is full and credentials did not reconnect
  if (!hasReconnected && this->lobbyIsFull()) {
    char l = 'l';
    this->socket->sndChar(&l, newSocket);
    return;
  }

  if (hasReconnected) {

    //Case has reconected send c to skip lobby
    char c = 'c';
    this->socket->sndChar(&c, newSocket);

  } else {
    if (this->configuration->checkCredentials(&username, &password_str)) {

      //Case new client
      this->addNewClient(credentials, newSocket);
      char o = 'o';
      this->socket->sndChar(&o, newSocket);

    } else {

      //Case wrong credentials
      char f = 'f';
      this->socket->sndChar(&f, newSocket);
    }
  }
}

void Server::handleEvents() {
  int levelHasTransitioned = false;

  //this is for the transitioning view. Refactor later
  int levelNumberBeforeHandlingEvent = this->game->getCurrentLevel();

  if (!this->started) return;

  pthread_mutex_lock(&this->mutex);
  bool empty = this->eventQueue->isEmpty();
  pthread_mutex_unlock(&this->mutex);

  if (!empty) {

    pthread_mutex_lock(&this->mutex);
    EventContainer eventContainer = this->eventQueue->pop();
    pthread_mutex_unlock(&this->mutex);

    //game changes by handling the event
    this->gameController->handleEvents(eventContainer.e, eventContainer.clientNum);
    //Check if the client has desconnected
    if (eventContainer.e.type == SDL_QUIT)
      this->clientSetToOffline(eventContainer.clientNum);
    //Check if the game is still running after handling the events
    if (!this->isRunning()) this->quit();
  }

  this->gameController->update();

  // gathers the positions to send them to the client

  this->game->getBossInfo(&this->positions.bossInfo);
  this->game->getPrincessInfo(&this->positions.princessInfo);
  this->game->getPLayerInfo(this->positions.playersInfo, &this->positions.playerCount);
  this->game->getPlatforms(this->positions.platforms, &this->positions.platformCount);
  this->game->getLadders(this->positions.ladders, &this->positions.ladderCount);
  this->game->getFires(this->positions.fires, &this->positions.fireCount);
  this->game->getEnemyFiresPos(this->positions.fireEnemies, &this->positions.fireEnemyCount);
  this->game->getBarrelsInfo(this->positions.barrels,&this->positions.barrelCount);

  levelHasTransitioned = this->checkIfTheLevelHasTransitioned(levelNumberBeforeHandlingEvent);
  pthread_mutex_lock(&this->mutex);
  if (!levelHasTransitioned) {
    this->broadcast();
  } else {
    SDL_Delay(1000);
    levelHasTransitioned = false;
  }

  pthread_mutex_unlock(&this->mutex);

}

void Server::receive(int clientNum, int socketNumber) {
  if (!this->started) return;
  SDL_Event e;
  if (this->socket->receive(&e, socketNumber) < 0) {
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

void Server::broadcastGameStart() {
  pthread_mutex_lock(&this->mutex);
  for (int i = 0; i < this->totalClientsCount; i++) {
    //char string[30];
    //strcpy(string,"confirmed");
    //this->socket->sndString(string, this->sockets[i]);
    //this->socket->snd(new Positions(),this->sockets[i]);
    char confirmation = 'c';
    this->socket->sndChar(&confirmation, this->sockets[i]);
  }
  this->started = true;
  Logger::log(Logger::Info, "Cantidad necesaria de jugadores alcanzada. Enviando confimarcion de comienzo de juego");
  SDL_Delay(1200);
  pthread_mutex_unlock(&this->mutex);
}

void Server::broadcastTransitionLevel() {
  pthread_mutex_lock(&this->mutex);
  for (int i = 0; i < this->totalClientsCount; i++) {
    char switchTransitionLevel = 's';
    this->socket->sndChar(&switchTransitionLevel, this->sockets[i]);
  }
  Logger::log(Logger::Info, "Cambia a la pantalla de transicion entre niveles");
  pthread_mutex_unlock(&this->mutex);
}

void Server::addNewClient(Credentials credentials, int newSocket) {
  //Allocate memory for a new socket
  int *tmpSocket = (int *) realloc(this->sockets, (this->totalClientsCount + 1) * sizeof(int));
  if (!tmpSocket) {
    Logger::log(Logger::Error, "Error al reservar memoria. Server::addNewConnection");
    return;
  }
  this->sockets = tmpSocket;

  //Create new ServerContainer(playerConnection)
  ServerContainer *container = new ServerContainer();
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
  while (!hasReconnected && !foundClient && (clientNumberToReconnect < this->totalClientsCount)) {
    foundClient = (this->clientConnections[clientNumberToReconnect]->username == credentials.username) &&
                  (this->clientConnections[clientNumberToReconnect]->password == credentials.password);
    //If found and is offline recconect it
    if (foundClient && !clientConnections[clientNumberToReconnect]->isOnline) {
      hasReconnected = true;
      this->reconnectClient(clientNumberToReconnect, newSocket);
    }

    clientNumberToReconnect++;
  }

  return hasReconnected;
}

bool Server::clientIsOnline(Credentials credentials) {
  bool found = false;
  int clientNumber = 0;

  while (!found && (clientNumber < this->totalClientsCount)) {
    ServerContainer *clientConnection = this->clientConnections[clientNumber];
    found = (clientConnection->isOnline) && (clientConnection->username == credentials.username)
            && (clientConnection->password == credentials.password);
    clientNumber++;
  }

  return found;
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

  //Send 'o' to confirm credentials
  char c = 'o';
  this->socket->sndChar(&c, newSocket);
  SDL_Delay(2000);

  //Player is active again (cambiar despues rompe encapsulamiento)
  this->game->getPlayer(clientNumberToReconnect)->startedPlaying();
  pthread_mutex_unlock(&this->mutex);

  //Create the thread to receive
  pthread_t receiveThread;
  pthread_create(&receiveThread, NULL, &receiveEvents, clientToReconnect);

  Logger::log(Logger::Debug, "se reconecto", clientNumberToReconnect);
}

void Server::clientSetToOffline(int clientNumber) {
  //Esto hay que sacarlo es un hotfix
  if (!clientConnections[clientNumber]->isOnline) return;

  pthread_mutex_lock(&this->mutex);
  clientConnections[clientNumber]->isOnline = false;

  this->onlineClientsCount--;
  this->offlineClientsCount++;
  pthread_mutex_unlock(&this->mutex);

  Logger::log(Logger::Info, "se desconecto", clientNumber);

  pthread_t accepter;
  pthread_create(&accepter, NULL, &reacceptConnections, this);
}

bool Server::lobbyIsFull() {
  return (this->totalClientsCount >= this->clientMax);
}

void Server::rejectConnection() {
  pthread_mutex_lock(&this->mutex);
  Logger::log(Logger::Info, "Esperando accept para rechazar");
  pthread_mutex_unlock(&this->mutex);
  //Create socket
  int newSocket = this->socket->accept();
  pthread_mutex_lock(&this->mutex);
  Logger::log(Logger::Info, "Se rechaza nueva conexion");
  pthread_mutex_unlock(&this->mutex);
  char l = 'l';
  this->socket->sndChar(&l, newSocket);
}

bool Server::checkIfTheLevelHasTransitioned(int levelNumberBeforeHandlingEvent) {
  if (levelNumberBeforeHandlingEvent != this->game->getCurrentLevel()) {
    if (levelNumberBeforeHandlingEvent < this->game->getCurrentLevel()) {
      // Pasar al segundo nivel
      this->broadcastLevelTransition();
      return true;
    } else if (levelNumberBeforeHandlingEvent > this->game->getCurrentLevel()) {
      // Termina el juego
      this->broadcastEndGame();
      return true;
    }
  }
  return false;
}

void Server::broadcastLevelTransition() {
  this->positions.transitioningLevel = true;

  pthread_mutex_lock(&this->mutex);
  this->broadcast();
  pthread_mutex_unlock(&this->mutex);
  SDL_Delay(5000);
  this->positions.transitioningLevel = false;

}

void Server::broadcastEndGame(){

  this->positions.endGame = true;

  pthread_mutex_lock(&this->mutex);
  this->broadcast();
  pthread_mutex_unlock(&this->mutex);
  SDL_Delay(5000);

}
