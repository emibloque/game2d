#pragma once

#include <list>

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Space.h"

#include <fstream>
#include <sstream>

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
  Actor *backgroundPoints;
  Text *textPoints;
  int points;

  bool controlShoot = false;
  int controlMoveY = 0;
  int controlMoveX = 0;

  int newEnemyTime = 0;

  void loadMap(string name);
  void loadMapObject(char character, int x, int y);
  int mapWidth;
  list<Tile *> tiles;

  void calculateScroll();
  float scrollX = 0;

  Space *space;
};
