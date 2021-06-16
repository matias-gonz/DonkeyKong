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

struct ServerContainer {
  Server *server;
  int clientNum;
  int socketNumber;
};

class Server {

public:

  Server(char *port, char *IP);

  bool isRunning();

  void start();

  bool isFull();

  void addNewConnection();

  void handleEvents();

  void broadcast();

  void broadcastString(char* message);

  void receive(int clientNum, int socketNumber);

  bool isPlayerConnected(int playerNumber);


private:
  ServerSocket *socket;
  Configuration *configuration;
  Game *game;
  GameController *gameController;
  Positions positions;
  QueueThrd *eventQueue;

  char *port;
  char *ip;
  int clientCount;
  int clientMax, clientsMin;
  int *sockets;
  pthread_mutex_t mutex;
  bool gameStarted;
  bool started;
  std::vector<char*> users;
  std::vector<ServerContainer*> containers;

  void quit();

  void gameStart();



};

#endif //TALLER_PROG_I_2021_1C_KIWI_SERVER_H
