#ifndef PREDICTENEMY_H
#define PREDICTENEMY_H

#include "predictenemy.h"

class PredictEnemy : public Enemy
{
    float lastTime;
    int count = 0;
    Vector2 playerLastPosition;

public:
    PredictEnemy(float hp, float genTime, float livetime, Vector2 pos, float r, char *filename);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition);
};

#endif