
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "../Position.h"
#include "../../view/Animator.h"
#include "../Entity.h"
#include "PlayerState.h"
#include "../Hammer.h"
#include "PlayerEvent.h"

class PlayerState;

class Player : public Entity {
private:
  int counter, gravity, hp, points;
  bool isClimbing, canClimb, active, canAddPoints, alive;
  PlayerState *modeState;
  PlayerEvent lastEvent;

  static const int VEL = 3;
public:
  explicit Player(Position *pos, char *string);

  ~Player();

  void addLeftVel();

  void addRightVel();

  void jumpUp();

  void resetVelX();

  void update();

  SDL_Rect getRectangle();

  void moveUp(int dy);

  void setGrounded();

  void resetVelY();

  int getVelY();

  void resetPos();

  Position *initialPos;

  bool isIn(Position *pPosition);

  void startClimbing(int i);

  void setCanClimb(bool canClimb);

  void stoppedPlaying();

  bool hasWon();

  bool getAddPoints();

  void setAddPoints();

  void cantAddPoints();

  bool isPlaying();

  char username[20];

  char *getUsername();

  void startedPlaying();

  void playerWon();

  void resetPlayerWon();

  void die();

  void takeDamage(Entity *pEntity);

  void takeNormalDamage();

  int getHp();

  int getPoints();

  void addPoints(int points);

  void normalUpdate();

  void winUpdate();

  bool isPlayingLevel(bool b);

  void switchGod();

  void grabHammer(Hammer ***hammers, int *hammerCount, int index);

  void killedAnEnemy();

  bool isAlive();

  void resetSpawn();

  char extractLastEvent();

    void mutedMusic();

    void mutedSoundEffects();

    void grabbedAHammer();

    void switchedToGod();

    bool hasHammer();

    void setNormal();
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
