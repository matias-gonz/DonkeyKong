#include "Game.h"


SDL_Renderer *Game::renderer = NULL;

Game::Game() {}

Game::~Game() {}

void Game::start(){
    this->running = true;
    this->level = new Level();
    this->level->loadLevel();
    this->player = new Player();
}


void Game::quit() {
    running = false;
}

bool Game::isRunning() {
    return this->running;
}

Level* Game::getLevel(){
    return this->level;
}

Player* Game::getPlayer() {
    return this->player;
}

