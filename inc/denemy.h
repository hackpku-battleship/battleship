#ifndef DENEMY_H
#define DENEMY_H

#include "enemy.h"

class DEnemy : public Enemy
{
public:
    DEnemy(float _hp, float _genTime, float livetime, float _x, float _y, float _r);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager);
    void draw();
};

#endif