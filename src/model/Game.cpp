#include "Game.h"

Game::Game() {}

Game::~Game() {
    delete this->player;
    delete this->level;
    delete this->enemyFire;
}

void Game::start(){
    this->running = true;
    this->level = new Level();
    this->loadLevel(1);
    this->player = new Player(new Position(200,200));
    this->enemyFire = new EnemyFire(new Position(250,250));
}


void Game::quit() {
    running = false;
}


void Game::update() {
    this->level->update();
    this->player->update();
    this->enemyFire->update();
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

EnemyFire *Game::getEnemyFire() {
    return this->enemyFire;
}
