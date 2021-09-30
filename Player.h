
#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Animation.h"

class Player : public Actor
{
public:
  Player(float x, float y, Game *game);

  void update();
  void moveX(int axis);
  void moveY(int axis);
  Projectile *shoot();

  int shootCadence = 30;
  int shootTime = 0;

  void draw(float scrollX = 0) override;
  Animation *aIdleLeft;
  Animation *aIdleRight;
  Animation *aRunningRight;
  Animation *aRunningLeft;
  Animation *aShootingRight;
  Animation *aShootingLeft;
  Animation *animation;

  Orientation orientation = Orientation::RIGHT;
  States state = States::IDLE;

  void jump();
  bool isOnAir = false;
};
