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
    FOR_INTERVAL(dutime, dtime, 1)
    {
        Vector2 predict = {2 * playerPosition.x - playerLastPosition.x, 2 * playerPosition.y - playerLastPosition.y};
        for (int i = 0; i < 1; i++)
        {
            Vector2 dv = normalize(predict - pos);
            Bullet *b = new basicBullet(nowTime, 15, creater, BLUE, 15, pos, 1000 * dv);
            ret.push_back(b);
        }
        playerLastPosition = playerPosition;
    }
    dutime = dtime;
    return ret;
}