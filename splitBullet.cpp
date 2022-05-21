#include "raylib.h"
#include "splitBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

splitBullet::splitBullet(float nowTime, float lifeTime, Color col, float radius,
                         Vector2 startPosition, Vector2 velocity,
                         std::vector<Bullet *> bullets, BulletManager *creater) : Bullet(nowTime, lifeTime, col, radius, startPosition),
                                                                                  velocity(velocity), bullets(bullets), creater(creater)
{
    // radius = 15;
}
float splitBullet::updateTime(float nowTime, Vector2 playerPosition)
{
    float deltaTime = Bullet::updateTime(nowTime, playerPosition);
    float dtime = nowTime - genTime;
    pos = pos + deltaTime * velocity;
    /*for(auto bullet:bullets) {
        std::cerr<<bullet->pos.x<<' '<<bullet->pos.y<<std::endl;
    }*/
    // position = position + deltaTime * velocity;
    dutime = dtime;
    return deltaTime;
}
splitBullet::~splitBullet()
{
    for (auto bullet : bullets)
    {
        bullet->genTime = bullet->lastTime = genTime + lifeTime;
        bullet->Move(pos);
        creater->addBullet(bullet);
    }
}