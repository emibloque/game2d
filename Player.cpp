#include "Player.h"

Player::Player(float x, float y, Game *game)
    : Actor("res/jugador.png", x, y, 35, 35, game)
{

    aIdleLeft = new Animation("res/jugador_idle_izquierda.png", width, height,
                              320, 40, 6, 8, game);
    aIdleRight = new Animation("res/jugador_idle_derecha.png", width, height,
                               320, 40, 6, 8, game);
    aRunningRight = new Animation("res/jugador_corriendo_derecha.png", width, height,
                                  320, 40, 6, 8, game);
    aRunningLeft = new Animation("res/jugador_corriendo_izquierda.png", width, height,
                                 320, 40, 6, 8, game);
    animation = aIdleRight;
}

void Player::update()
{
    animation->update();

    if (shootTime > 0)
    {
        shootTime--;
    }

    // Update Orientation
    if (vx > 0)
    {
        orientation = Orientation::RIGHT;
    }
    else if (vx < 0)
    {
        orientation = Orientation::LEFT;
    }

    // Update state
    if (vx != 0)
    {
        state = States::MOVING;
    }
    else
    {
        state = States::IDLE;
    }

    // Update animation
    switch (state)
    {
    case States::MOVING:
        animation = orientation == Orientation::RIGHT ? aRunningRight : aRunningLeft;
        break;

    default:
        animation = orientation == Orientation::RIGHT ? aIdleRight : aIdleLeft;
        break;
    }

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

Projectile *Player::shoot()
{
    if (shootTime == 0)
    {
        shootTime = shootCadence;
        return new Projectile(x, y, game);
    }
    else
    {
        return nullptr;
    }
}

void Player::draw()
{
    animation->draw(x, y);
}
