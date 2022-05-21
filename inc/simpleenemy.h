#ifndef SIMPLEENEMY_H
#define SIMPLEENEMY_H

#include "enemy.h"

class SimpleEnemy : public Enemy
{
    float rotatep;

public:
    SimpleEnemy(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition);
};
#endif