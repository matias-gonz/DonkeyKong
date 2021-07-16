
#ifndef TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
#define TALLER_PROG_I_2021_1C_KIWI_PLAYER_H


#include "../Position.h"
#include "../../view/Animator.h"
#include "../Entity.h"
#include "PlayerState.h"

class PlayerState;

class Player : public Entity {
private:
  int counter, gravity, hp, points;
  bool isClimbing, canClimb, active, hasWon, canAddPoints;
  //PlayerState *state;

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

  void moveDown(int i);

  int getVelY();

  void resetPos();

  Position *initialPos;

  bool isIn(Position *pPosition);

  void startClimbing(int i);

  void setCanClimb(bool canClimb);

  void stoppedPlaying();

  bool hasplayerWon();

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

  void takeDamage();

  bool dead;

  PlayerState *modeState;

  void takeNormalDamage();

  int getHp();

  int getPoints();

  void addPoints(int points);

  void normalUpdate();

    void winUpdate();

    bool isPlayingLevel(bool b);
};


#endif //TALLER_PROG_I_2021_1C_KIWI_PLAYER_H
