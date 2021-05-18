#include "Game.h"

Game::Game() {}

Game::~Game() {
    delete this->player;
    delete this->level;
    delete this->enemyFire;
}

void Game::start() {
    this->running = true;
    this->level = new Level();
    this->loadLevel(1);
    this->player = new Player(new Position(200,540));
    this->enemyFire = new EnemyFire(new Position(250,250));
    this->boss = new Boss(new Position(200,0));
    this->princess = new Princess(new Position(450,30));
}


void Game::quit() {
    running = false;
}


void Game::update() {
    this->level->update();
    this->princess->update();
    this->enemyFire->update();
    this->player->update();
    this->boss->update();
}

bool Game::isRunning() {
    return this->running;
}

Level *Game::getLevel() {
    return this->level;
}

Player *Game::getPlayer() {
    return this->player;
}

void Game::loadLevel(int levelnum) {
    this->level->loadLevel(levelnum);
}

EnemyFire *Game::getEnemyFire() {
    return this->enemyFire;
}

Boss *Game::getBoss() {
    return this->boss;
}

Princess *Game::getPrincess() {
    return this->princess;
}
