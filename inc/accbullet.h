#ifndef ACCBULLET_H
#define ACCBULLET_H

#include "bullet.h"

// 加速弹，有x,y两个方向上的加速度
class accBullet : public Bullet {
public:
    Vector2 acc, vel;
    accBullet(float nowTime, float liveTime, Color col, float radius, Vector2 _pos, Vector2 _velocity, Vector2 _acc);
    float updateTime(float, Vector2);
};

#endif
