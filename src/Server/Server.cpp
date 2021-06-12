#include "Server.h"

Server::Server(char *port, char *IP) {

    this->configuration = new Configuration();
    Logger::startLogger(this->configuration, "server.log");
    this->game = new Game(this->configuration);
    this->game->start();
    this->gameController = new GameController(this->game);
    this->eventQueue = cola_crear();
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
}

void* Server::updateThread(void* socket) {
    auto* s = (ServerSocket*)socket;
    game->addPlayer();
    while(true){
        SDL_Event e;
        s->receive(&e);
        SDL_Event* event = new SDL_Event(e);
        cola_encolar(eventQueue,event);
    }
}

bool Server::isRunning() {
    return this->game->isRunning();
}


void Server::update() {
    while(true){
        SDL_Event* e = static_cast<SDL_Event *>(cola_desencolar(eventQueue));
        gameController->handleEvents(*e,pthread_self());
        gameController->update();
        plyrPos.playerX = game->getPlayer(pthread_self())->getXPosition();
        plyrPos.playerY = game->getPlayer(pthread_self())->getYPosition();
        delete e;
        broadcast();
    }
}

void Server::broadcast() {
    for(int i = 0; i < 4;i++){
        sockets[i]->snd(&plyrPos);
    }
}
