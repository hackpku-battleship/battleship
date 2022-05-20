#include "player.h"
#include "raylib.h"

PlayerHPBar::PlayerHPBar(float x, float y, float radius, float delta)
    : x(x), y(y), radius(radius), delta(delta)
{
}

void PlayerHPBar::Draw(int hp)
{
    for (int i = 0; i < hp; i++)
        DrawCircleV({x + delta * i, y}, radius, MAROON);
}

Player::Player(Vector2 position, float radius, int hp, float speed, float minY, float hitlessTime)
    : position(position), radius(radius), hp(hp), speed(speed), minY(minY), hitlessTime(hitlessTime)
{
}

void Player::Hit(float nowTime)
{
    if (canHit)
    {
        hp -= 1;
        canHit = false;
        lastHitTime = nowTime;
    }
}

void Player::Update(float nowTime)
{
    if (nowTime - lastHitTime > hitlessTime)
        canHit = true;
}

void Player::Move()
{
    if (IsKeyDown(KEY_UP))
        position.y -= speed;
    if (IsKeyDown(KEY_DOWN))
        position.y += speed;
    if (IsKeyDown(KEY_LEFT))
        position.x -= speed;
    if (IsKeyDown(KEY_RIGHT))
        position.x += speed;
    if (position.y < minY)
        position.y = minY;
    if (position.y > GetScreenHeight())
        position.y = GetScreenHeight();
    if (position.x < 0)
        position.x = 0;
    if (position.x > GetScreenWidth())
        position.x = GetScreenWidth();
}

void Player::Draw()
{
    DrawCircleV(position, radius, MAROON);
}

int Player::getHP()
{
    return hp;
}

Vector2 Player::getPosition()
{
    return position;
}

float Player::getRadius()
{
    return radius;
}
