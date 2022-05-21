#include "enemy.h"
#include "predictenemy.h"
#include "basicBullet.h"
#include "Vector2Basic.h"
#include <iostream>

PredictEnemy::PredictEnemy(float hp, float gentime, float livetime, Vector2 pos, float r, char *filename) : Enemy(hp, gentime, livetime, pos, r, filename)
{
    lastTime = gentime;
}

std::vector<Bullet *> PredictEnemy::getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition)
{
    std::vector<Bullet *> ret;
    float dtime = nowTime - gentime;
    if (int(dtime * 0.2) - int(dutime * 0.2) >= 1)
    {
        Bullet *b = new fishBullet(nowTime, 20, creater, PURPLE, 15, pos, 200, PI / 2);
        ret.push_back(b);
    }
    if (int(dtime * 2) - int(dutime * 2) >= 1)
    {
        Vector2 dir = {playerPosition.x - playerLastPosition.x, playerPosition.y - playerLastPosition.y};
        Vector2 velocity = {dir.x / (nowTime - lastTime), dir.y / (nowTime - lastTime)};
        float time = sqrt((pos.x - playerPosition.x) * (pos.x - playerPosition.x) + (pos.y - playerPosition.y) * (pos.y - playerPosition.y)) / 1000;
        Vector2 predict = {playerPosition.x + time * velocity.x, playerPosition.y + time * velocity.y};
        float ang = atan2(predict.y - pos.y, predict.x - pos.x);
        Vector2 f = {cos(ang), sin(ang)};
        Bullet *b = new basicBullet(nowTime, 15, creater, BLUE, 15, pos, {1000 * f.x, 1000 * f.y});
        ret.push_back(b);
        lastTime = nowTime;
    }
    if (int(dtime * 10) - int(dutime * 10) >= 1)
    {
        playerLastPosition = playerPosition;
        lastTime = nowTime;
    }
    dutime = dtime;
    return ret;
}