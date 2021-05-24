#include "Server.h"


int createSocketServer(const char *port, char *IP) {

  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
    Logger::log(Logger::Error,"Error al crear el socket");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port 8080
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    Logger::log(Logger::Error,"Error al crear el setSockOpt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  try {
    address.sin_port = htons(atoi(port));
  } catch (const std::exception& e) {
    Logger::log(Logger::Error,"Error al crear el puerto");
  }

  // Forcefully attaching socket to the port 8080
  if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
    Logger::log(Logger::Error,"Error al bindear el socket al puerto");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0) {
    Logger::log(Logger::Error,"Error al escuchar el socket");
    exit(EXIT_FAILURE);
  }

  return 0;
}

Server::Server(char **port, char **IP) {

  Configuration *configuration = new Configuration();
  Logger::startLogger("log.txt", configuration);
  Game *game = new Game(configuration);
  game->start();

  GameController *gameController = new GameController(game);
  ViewManager *viewManager = new ViewManager(game, configuration, "Donkey Kong", SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             1024, 576, false);

  while (game->isRunning()) {
    gameController->handleEvents();
    gameController->update();
    viewManager->renderWindow();
  }

  int socketServer = createSocketServer(*port, *IP);

  delete game;

}