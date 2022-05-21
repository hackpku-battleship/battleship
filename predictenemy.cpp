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
    if (int(dtime * 2) - int(dutime * 2) >= 1)
    {
        Vector2 predict = {2 * playerPosition.x - playerLastPosition.x, 2 * playerPosition.y - playerLastPosition.y};
        for (int i = 0; i < 1; i++)
        {
            float ang = atan2(predict.y - pos.y, predict.x - pos.x) + 0.30 * rand() / RAND_MAX;
            Vector2 f = {cos(ang), sin(ang)};
            Bullet *b = new basicBullet(nowTime, 15, creater, BLUE, 30, pos, {3000 * f.x, 3000 * f.y});
            ret.push_back(b);
        }
        playerLastPosition = playerPosition;
    }
    dutime = dtime;
    return ret;
}