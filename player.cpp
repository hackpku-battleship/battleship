#include "player.h"
#include "raylib.h"

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
    DrawCircleV(position, 10, MAROON);
    for (int i = 0; i < hp; i++)
        DrawCircleV({20.0f + 20.0f * i, (float)GetScreenHeight() - 20}, 10, MAROON);
}