#include "Player.h"

Player::Player(float x, float y, Game *game)
    : Actor("res/jugador.png", x, y, 50, 57, game)
{
}

void Player::update()
{
    x = x + vx;
    y = y + vy;
}

void Player::moveX(int axis)
{
    vx = axis * 3;
}

void Player::moveY(int axis)
{
    vy = axis * 3;
}