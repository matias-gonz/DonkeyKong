#include "Game.h"

Game::Game() {}

Game::~Game() {
    delete this->player;
    delete this->level;
}

void Game::start(){
    this->running = true;
    this->level = new Level();
    this->loadLevel(1);
    this->player = new Player(new Position(200,200));
}


void Game::quit() {
    running = false;
}


void Game::update() {
    this->level->update();
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

void Game::loadLevel(int levelnum) {
    this->level->loadLevel(levelnum);
}

