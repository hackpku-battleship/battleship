#ifndef SIMPLEENEMY_H
#define SIMPLEENEMY_H

#include "enemy.h"

class SimpleEnemy : public Enemy
{
    float rotatep;

public:
    SimpleEnemy(float _hp, float _genTime, float livetime, float _x, float _y, float _r, char* filename);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *creater);
    void draw();
};
#endif