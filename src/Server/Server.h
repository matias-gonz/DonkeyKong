#ifndef TALLER_PROG_I_2021_1C_KIWI_SERVER_H
#define TALLER_PROG_I_2021_1C_KIWI_SERVER_H

#include <SDL2/SDL_events.h>
#include <netinet/in.h>
#include <pthread.h>
#include "../model/Game.h"
#include "../model/Logger.h"
#include "../Constants.h"
#include "../view/ViewManager.h"
#include "../controller/GameController.h"
#include "../controller/Configuration.h"
#include "../Socket/ServerSocket.h"
#include "../controller/QueueThrd.h"

class Server;

struct ServerContainer {
  Server *server;
  int clientNum;
  int socketNumber;
  std::string username, password;
  bool isOnline;
};

class Server {

public:

  Server(char *port, char *IP);

  bool isRunning();

  void start();

  bool hasAllClientsOnline();

  void addNewConnection();

  void handleEvents();

  void broadcast();

  void receive(int clientNum, int socketNumber);

  bool isPlayerConnected(int playerNumber);

  void broadcastGameStart();

  void broadcastTransitionLevel();

  void rejectConnection();

    bool hasNoClientsOnline();

private:
  ServerSocket *socket;
  Configuration *configuration;
  Game *game;
  GameController *gameController;
  Positions positions;
  QueueThrd *eventQueue;

  char *port;
  char *ip;
  int totalClientsCount;
  int onlineClientsCount;
  int offlineClientsCount;
  int clientMax;
  int *sockets;
  pthread_mutex_t mutex;
  bool started;
  std::vector<ServerContainer *> clientConnections;

  bool clientsPlaying();

  bool _clientsPlaying;

  void quit();

  void addNewClient(Credentials credentials, int newSocket);

  bool tryToReconnectUsing(Credentials credentials, int i);

  bool clientIsOnline(Credentials credentials);

  void reconnectClient(int i, int i1);

  void clientSetToOffline(int i);

  bool lobbyIsFull();

  bool checkIfTheLevelHasTransitioned(int levelNumberBeforeHandlingEvent);

  void broadcastLevelTransition();

  void broadcastEndGame();
};

#endif //TALLER_PROG_I_2021_1C_KIWI_SERVER_H
