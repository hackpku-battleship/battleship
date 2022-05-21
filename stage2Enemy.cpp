#include "enemy.h"
#include "stage2Enemy.h"
#include "Vector2Basic.h"
#include <iostream>
#include "utils.h"

stage2Enemy::stage2Enemy(float _hp, float _gentime, float _livetime, Vector2 pos, float _r, char *filename) : 
    Enemy(_hp, _gentime, _livetime, pos, _r, filename){}

std::vector<Bullet *> stage2Enemy::getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition)
{
    float dtime = nowTime - gentime;
    std::vector<Bullet *> ret;
    if (dtime <= 10) 
    {
        FOR_INTERVAL(dutime, dtime, 2) {
            float bias = getrand(-PI / 4, PI / 4);
            for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 8) {
                //float randtime = getrand(0, 1.5);
                Vector2 f1 = {cos(alpha + bias), sin(alpha + bias)};
                for (float beta = 0.0; beta <= PI * 2; beta += PI / 16) {
                    Vector2 f2 = {cos(beta), sin(beta)};
                    Bullet *b = new TurningBullet(nowTime, 10, creater, LIME, 5, 
                    pos + f1, 300 * f1, 50 * f2, 1 + getrand(0, 1.5));
                    ret.push_back(b);
                }
                Bullet *b = new basicBullet(nowTime, 5, creater, VIOLET, 8, pos + f1, 300 * f1);
                ret.push_back(b);
            }
        }
    }
    else if (dtime >= 14 && dtime <= 24) {
        FOR_INTERVAL(dutime, dtime, 2) {
            float bias = getrand(-PI / 4, PI / 4);
            for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 4) {
                Vector2 f1 = {cos(alpha + bias), sin(alpha + bias)};
                for (float turnt = 1; turnt <= 3; turnt += 0.2) {
                    for (float beta = 0.0; beta <= PI * 2; beta += PI / 4) {
                        Vector2 f2 = {cos(beta), sin(beta)};
                        Bullet *b = new TurningBullet(nowTime, 10, creater, BLACK, 5,
                        pos + f1, 300 * f1, 50 * f2, turnt);
                        ret.push_back(b);
                    }
                }
            }
        }
    }
    dutime = dtime;
    return ret;
}