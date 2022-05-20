#include "player.h"
#include "raylib.h"

void Player::Move()
{
    position = GetMousePosition();
}
void Player::Draw()
{
    DrawCircleV(position, 40, MAROON);
}