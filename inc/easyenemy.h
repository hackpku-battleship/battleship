#ifndef EASYENEMY_H
#define EASYENEMY_H

#include "enemy.h"

class EasyEnemy : public Enemy
{
    float lastTime;
    int count = 0;

public:
    EasyEnemy(float hp, float genTime, float livetime, Vector2 pos, float r, char *filename);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition);
};

#endif