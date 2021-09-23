#pragma once

#include <list>

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"

class GameLayer : public Layer
{
public:
  GameLayer(Game *game);
  void init() override;
  void processControls() override;
  void update() override;
  void draw() override;
  void keysToControls(SDL_Event event);

  Player *player;
  list<Enemy *> enemies;
  list<Projectile *> projectiles;

  Background *background;

  bool controlShoot = false;
  int controlMoveY = 0;
  int controlMoveX = 0;

  int newEnemyTime = 0;
};
