#pragma once

#include "Game.h"

class Text
{
public:
  Text(string content, int x, int y, Game *game);
  void draw();

  string content;
  int x, y, width, height;
  Game *game;
};
