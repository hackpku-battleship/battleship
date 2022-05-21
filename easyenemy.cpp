#include "enemy.h"
#include "easyenemy.h"
#include "basicBullet.h"
#include "Vector2Basic.h"
#include "utils.h"
#include <iostream>

EasyEnemy::EasyEnemy(float hp, float gentime, float livetime, Vector2 pos, float r, char *filename) : Enemy(hp, gentime, livetime, pos, r, filename)
{
    lastTime = gentime;
}

std::vector<Bullet *> EasyEnemy::getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition)
{
    std::vector<Bullet *> ret;
    float dtime = nowTime - gentime;
    FOR_INTERVAL(dutime, dtime, 1.5) {
        for (float ang = 0; ang <= PI * 2 ; ang += PI / 8)
        {
            float _ang = ang + getrand(-PI / 8, PI / 8);// + (PI / 64) * (count % 4);
            Vector2 f = {cos(_ang), sin(_ang)};
            Bullet *b = new accBullet(nowTime, 15, creater, PURPLE, 10, pos, {100 * f.x, 100 * f.y}, {200 * f.x, 200 * f.y});
            ret.push_back(b);
        }
        count++;
        lastTime = nowTime;
    }
    dutime = nowTime - gentime;
    return ret;
}