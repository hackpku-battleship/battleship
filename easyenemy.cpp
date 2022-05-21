#include "enemy.h"
#include "easyenemy.h"
#include "basicBullet.h"
#include "Vector2Basic.h"
#include <iostream>

EasyEnemy::EasyEnemy(float hp, float gentime, float livetime, Vector2 pos, float r, char *filename) : Enemy(hp, gentime, livetime, pos, r, filename)
{
    lastTime = gentime;
}

std::vector<Bullet *> EasyEnemy::getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition)
{
    std::vector<Bullet *> ret;
    if (nowTime - lastTime >= 1.0 / int(sqrt(dutime)))
    {
        for (float ang = 0; ang <= PI; ang += PI / 16)
        {
            float _ang = ang + (PI / 64) * (count % 4);
            Vector2 f = {cos(_ang), sin(_ang)};
            Bullet *b = new accBullet(nowTime, 15, creater, PURPLE, 25, pos, {200 * f.x, 200 * f.y}, {50 * f.x, 50 * f.y});
            ret.push_back(b);
        }
        count++;
        lastTime = nowTime;
    }
    dutime = nowTime - gentime;
    return ret;
}