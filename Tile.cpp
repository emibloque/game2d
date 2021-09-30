#include "Tile.h"

Tile::Tile(string filename, int x, int y, Game *game)
    : Actor(filename, x, y, 40, 32, game)
{
}
