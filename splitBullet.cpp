#include "raylib.h"
#include "splitBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

splitBullet::splitBullet(float nowTime, float lifeTime, Vector2 startPosition, Vector2 velocity, float speed, BulletManager *creater) : Bullet(nowTime, lifeTime), position(startPosition), velocity(velocity), speed(speed), creater(creater)
{
    radius = 15;
}
float splitBullet::updateTime(float nowTime, Vector2 playerPosition)
{
    float deltaTime = Bullet::updateTime(nowTime, playerPosition);
    float dtime = nowTime - genTime;
    position = position + deltaTime * velocity;
    if (int(dtime * speed) - int(dutime * speed) >= 1)
    {
        for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 2)
        {
            Vector2 f = {cos(alpha), sin(alpha)};
            Bullet *b = new fishBullet(nowTime, 30.0, position + 10.0f * f, 200, alpha);
            creater->addBullet(b);
        }
    }
    // position = position + deltaTime * velocity;
    dutime = dtime;
    return deltaTime;
}
void splitBullet::Draw()
{
    DrawCircleV(position, radius, GREEN);
}
bool splitBullet::checkBox(Vector2 center, float rad)
{
    return CheckCollisionCircles(position, radius, center, rad);
}
bool splitBullet::inScreen(int H, int W)
{
    return 0 <= position.x && position.x < H && 0 <= position.y && position.y < W;
}