#include "Enemy.h"

Enemy::Enemy(float x, float y, Game *game)
    : Actor("res/enemigo.png", x, y, 36, 40, game)
{
  vx = 1;
}

void Enemy::update()
{
  x = x + vx;
  if (x <= 0 || x >= WIDTH)
  {
    vx = vx * -1;
  }
}
