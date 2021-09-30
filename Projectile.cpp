
#include "Projectile.h"

Projectile::Projectile(float x, float y, Game *game) : Actor("res/disparo_jugador.png", x, y, 18, 6, game)
{
  vx = 9;
  vy = -1;
}

void Projectile::update()
{
  vy = vy - 1;
}
