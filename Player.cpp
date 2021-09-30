#include "Player.h"

Player::Player(float x, float y, Game *game)
    : Actor("res/jugador.png", x, y, 35, 35, game)
{

    aIdleLeft = new Animation("res/jugador_idle_izquierda.png", width, height,
                              320, 40, 6, 8, true, game);
    aIdleRight = new Animation("res/jugador_idle_derecha.png", width, height,
                               320, 40, 6, 8, true, game);
    aRunningRight = new Animation("res/jugador_corriendo_derecha.png", width, height,
                                  320, 40, 6, 8, true, game);
    aRunningLeft = new Animation("res/jugador_corriendo_izquierda.png", width, height,
                                 320, 40, 6, 8, true, game);
    aShootingRight = new Animation("res/jugador_disparando_derecha.png", width, height,
                                   160, 40, 6, 4, false, game);
    aShootingLeft = new Animation("res/jugador_disparando_izquierda.png", width, height,
                                  160, 40, 6, 4, false, game);
    aJumpingLeft = new Animation("res/jugador_saltando_izquierda.png", width, height,
                                 160, 40, 6, 4, false, game);
    aJumpingRight = new Animation("res/jugador_saltando_derecha.png", width, height,
                                  160, 40, 6, 4, false, game);
    animation = aIdleRight;
}

void Player::update()
{
    if (invulnerableTime > 0)
    {
        invulnerableTime--;
    }

    bool hasAnimationEnded = animation->update();

    isOnAir = !collisionDown;

    if (hasAnimationEnded)
    {
        if (state == States::SHOOTING)
        {
            state = States::IDLE;
        }
    }

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
    if (state != States::SHOOTING)
    {
        if (vx != 0)
        {
            state = States::MOVING;
        }
        else
        {
            state = States::IDLE;
        }
    }

    if (isOnAir)
    {
        state = States::JUMPING;
    }

    // Update animation
    switch (state)
    {
    case States::SHOOTING:
        animation = orientation == Orientation::RIGHT ? aShootingRight : aShootingLeft;
        break;
    case States::MOVING:
        animation = orientation == Orientation::RIGHT ? aRunningRight : aRunningLeft;
        break;

    default:
        animation = orientation == Orientation::RIGHT ? aIdleRight : aIdleLeft;
        break;
    }
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
        state = States::SHOOTING;
        shootTime = shootCadence;
        auto projectile = new Projectile(x, y, game);
        if (orientation == Orientation::LEFT)
        {
            projectile->vx *= -1;
        }
        return projectile;
    }
    else
    {
        return nullptr;
    }
}

void Player::draw(float scrollX)
{
    if (invulnerableTime == 0)
    {
        animation->draw(x - scrollX, y);
        return;
    }
    if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5)
    {
        animation->draw(x - scrollX, y);
    }
}

void Player::jump()
{
    if (!isOnAir)
    {
        vy = -16;
        isOnAir = true;
    }
}

void Player::loseLife()
{
    if (invulnerableTime > 0 || lifes <= 0)
    {
        return;
    }

    lifes--;
    invulnerableTime = 100;
}
