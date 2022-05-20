#include "simpleenemy.h"

SimpleEnemy::SimpleEnemy(float _hp, float _gentime, float _x, float _y, float _r):
    Enemy(_hp, _gentime, _x, _y, _r) {}

std::vector<Bullet> SimpleEnemy::getBullet(float nowTime) {
    float dtime = nowTime - gentime;
    std::vector<Bullet> ret;
    if (dutime <= 0.5 && dtime >= 0.5) {
        ret.push_back((basicBullet){nowTime, (Vector2){x, y}, (Vector2){0, 1}});
    }
    dutime = dtime;
    return ret;
}