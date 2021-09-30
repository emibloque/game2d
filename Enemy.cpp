#include "Enemy.h"

Enemy::Enemy(float x, float y, Game *game)
    : Actor("res/enemigo.png", x, y, 36, 40, game)
{
  vxIntelligence = -1;
  vx = vxIntelligence;

  aDying = new Animation("res/enemigo_morir.png", width, height,
                         280, 40, 6, 8, false, game);

  aMoving = new Animation("res/enemigo_movimiento.png", width, height,
                          108, 40, 6, 3, true, game);
  animation = aMoving;
}

void Enemy::update()
{
  bool animationEnded = animation->update();

  if (animationEnded)
  {
    if (state == States::DYING)
    {
      state = States::DEAD;
    }
  }

  switch (state)
  {
  case States::DYING:
    vx = 0;
    animation = aDying;
    break;

  case States::MOVING:
    animation = aMoving;

    if (vx == 0)
    {
      vxIntelligence *= -1;
      vx = vxIntelligence;
    }
    break;
  }
}

void Enemy::draw(float scrollX)
{
  animation->draw(x - scrollX, y);
}

void Enemy::impacted()
{
  if (state != States::DYING)
  {
    state = States::DYING;
  }
}
