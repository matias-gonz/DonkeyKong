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
    for(int i = 0; i <enemyFireCount; i++){
        //this->enemyFires[i]->update();
    }
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
    this->resetEnemies();
    this->spawnEnemies(this->level->getSpawns(), this->level->getSpawnCount());
}

EnemyFire *Game::getEnemyFire() {
    return this->enemyFire;
}

void Game::spawnEnemies(Position **spawns, int spawnCount) {
    srand(time(NULL));
    for(int i = 0; i < spawnCount; i++){
        if((rand()%100) < 100){
            this->enemyFires = (EnemyFire **) (realloc(this->enemyFires, (this->enemyFireCount + 1) * sizeof(EnemyFire *)));
            EnemyFire* enemy = new EnemyFire(spawns[i]);
            this->enemyFires[this->enemyFireCount] = enemy;
            (this->enemyFireCount)++;
        }
    }
}

EnemyFire **Game::getEnemyFires() {
    return this->enemyFires;
}

int Game::getEnemyFireCount() {
    return this->enemyFireCount;
}

void Game::resetEnemies() {
    for(int i = 0; i < this->enemyFireCount; i++){
        delete this->enemyFires[i];
    }
    free(this->enemyFires);
    this->enemyFires = NULL;
    this->enemyFireCount = 0;
}
