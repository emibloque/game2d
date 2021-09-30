#include "Enemy.h"

Enemy::Enemy(float x, float y, Game *game)
    : Actor("res/enemigo.png", x, y, 36, 40, game)
{
  vx = 1;

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
    animation = aDying;
    break;

  case States::MOVING:
    animation = aMoving;

    vx = -1;
    x = x + vx;
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
