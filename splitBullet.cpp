#include "raylib.h"
#include "splitBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

splitBullet::splitBullet(float nowTime, float lifeTime, BulletManager *creater, Color col, float radius, 
                        Vector2 startPosition, Vector2 velocity, float speed): 
                Bullet(nowTime, lifeTime, creater, col, radius, startPosition),
    velocity(velocity), speed(speed)
{
    radius = 5;
}
float splitBullet::updateTime(float nowTime, Vector2 playerPosition)
{
    float deltaTime = Bullet::updateTime(nowTime, playerPosition);
    float dtime = nowTime - genTime;
    pos = pos + deltaTime * velocity;
    if (int(dtime * speed) - int(dutime * speed) >= 1)
    {
        for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 16)
        {
            Vector2 f = {cos(alpha), sin(alpha)};
            Bullet *b = new basicBullet(nowTime, 15.0, from, col, radius, pos + 10.0f * f, 50.0f * f);
            from->addBullet(b);
        }
    }
    // position = position + deltaTime * velocity;
    dutime = dtime;
    return deltaTime;
}
