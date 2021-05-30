#include "Game.h"

Game::Game(Configuration* configuration) {
  this->configuration = configuration;
}

Game::~Game() {
    delete this->player;
    delete this->level;
    for(int i = 0; i < this->enemyFireCount; i++){
        delete this->enemyFires[i];
    }
    free(this->enemyFires);
}

void Game::start() {
    this->running = true;
    this->level = new Level();
    this->loadLevel(1);
    this->player = new Player(new Position(200,525));
    Logger::log(Logger::Info,"Inicio Donkey Kong");
    this->boss = new Boss(new Position(100,35));
    this->princess = new Princess(new Position(450,30));
}

void Game::quit() {
    running = false;
}

void Game::update() {
    if(this->level->playerWon(this->player)){
        this->switchLevel();
        return;
    }
    this->level->update();
    this->player->update();
    for(int i = 0; i <enemyFireCount; i++){
        this->enemyFires[i]->update();
    }
    this->princess->update();
    this->boss->update();
    this->resolveCollisions();
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
    this->currentLevel = levelnum;
    this->level->loadLevel(levelnum, this->configuration);
    this->resetEnemies();
    //level should spawn enemies, not game
    this->spawnEnemies(this->level->getSpawns(), this->level->getSpawnCount(), this->configuration->getEnemiesCount());
}

void Game::spawnEnemies(Position **spawns, int spawnCount, int probability) {
    Logger::log(Logger::Info,"Se spawnean enemigos type_1");
    srand(time(NULL));
    for(int i = 0; i < spawnCount; i++){
        if((rand()%100) < probability){
            this->enemyFires = (EnemyFire **) (realloc(this->enemyFires, (this->enemyFireCount + 1) * sizeof(EnemyFire *)));
            if(!this->enemyFires){
                Logger::log(Logger::Error,"Error al reservar memoria. Game::spawnEnemies");
                return;
            }
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

void Game::switchLevel() {
    this->player->resetPos();
    if(this->currentLevel == 1){
        this->loadLevel(2);
    }else{
        this->loadLevel(1);
    }
}

Boss *Game::getBoss() {
    return this->boss;
}

Princess *Game::getPrincess() {
    return this->princess;
}

void Game::resolveCollisions() {
    this->level->resolveCollisions(this->player, this->enemyFires, this->enemyFireCount);


}
