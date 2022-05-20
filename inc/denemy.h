#ifndef DENEMY_H
#define DENEMY_H

#include "enemy.h"

class DEnemy : public Enemy
{
public:
    DEnemy(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager);
};

#endif