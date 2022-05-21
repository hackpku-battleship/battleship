#ifndef PREDICTENEMY_H
#define PREDICTENEMY_H

#include "predictenemy.h"

class PredictEnemy : public Enemy
{
    float predictLastTime, accLastTime;
    Vector2 playerLastPosition;
    int state, stateLastTime;
    int accCount = 0;
    float stateLengths[5] = {0, 10, 10, 10, 13};

public:
    PredictEnemy(float hp, float genTime, float livetime, Vector2 pos, float r, char *filename);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition);
};

#endif