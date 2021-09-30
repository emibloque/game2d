#pragma once

#include "Actor.h"
#include "Animation.h"

class Enemy : public Actor
{
public:
  Enemy(float x, float y, Game *game);
  void update();
  void draw() override;

  void impacted();
  States state = States::MOVING;

  Animation *aMoving;
  Animation *aDying;
  Animation *animation;
};
