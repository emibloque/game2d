#pragma once

#include "Actor.h"

class Tile : public Actor
{
public:
  Tile(string filename, int x, int y, Game *game);
};
