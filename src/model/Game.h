#ifndef TALLER_PROG_I_2021_1C_KIWI_GAME_H
#define TALLER_PROG_I_2021_1C_KIWI_GAME_H

#include "player/Player.h"
#include "Level.h"
#include "EnemyFire.h"
#include "Boss.h"
#include "Princess.h"
#include "../controller/Configuration.h"
#include "Logger.h"
#include "Hammer.h"

class Game {

public:
  Game(Configuration *configuration);

  ~Game();

  void start();

  void update();

  void quit();

  bool isRunning();

  Level *getLevel();

  Player *getPlayer(int i);

  void loadLevel(int i);

  Boss *getBoss();

  Princess *getPrincess();

  EnemyFire **getEnemyFires();

  int getEnemyFireCount();

  void switchLevel();

  void addPlayer(char string[20]);

  void getPlatforms(PlatformContainer *platforms, int *count);

  void getLadders(LadderContainer *ladders, int *count);

  void getFires(FireContainer *fires, int *count);

  void getEnemyFiresPos(EntityContainer *enemyFires, int *count);

  void getPLayerInfo(PlayersInformation *playerInfo, int *playerCount);

  void getBossInfo(EntityContainer *bossInfo);

  void getPrincessInfo(EntityContainer *princessInfo);

  int getPlayerCount();

  void updateStatus();

  bool isPlayerActive(int playerNumber);

  bool allPlayersAreDead();

  int getCurrentLevel();

  void getBarrelsInfo(EntityContainer *barrels, int *barrelCount);

  void getHammersInfo(EntityContainer *hammers, int *hammersCount);

  void switchGod(int i);

private:
  EnemyFire **enemyFires = NULL;
  int enemyFireCount = 0;
  Boss *boss = NULL;
  Princess *princess = NULL;
  bool running;
  Level *level;
  Configuration *configuration;
  int playersCountWon;
  Hammer **hammers = NULL;
  int hammersCount = 0;

  void spawnEnemies(Position **spawns, int spawnCount, int probability);

  void resetEnemies();

  int currentLevel;

  void resolveCollisions();

  void getEntityInfo(EntityContainer *entityInfo, Entity *entity);

  Player **players;
  int playerCount;

  bool anyPlayerWon();

  bool everyPlayerWon();

  void addPointsPodium(int playerNumber, int position);

  void checkWinners();

  bool levelIsOver();

  void resetHammers();

  void spawnHammers(Position **spawns, int spawnCount, int probability);

};


#endif //TALLER_PROG_I_2021_1C_KIWI_GAME_H
