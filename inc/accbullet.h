#ifndef ACCBULLET_H
#define ACCBULLET_H

#include "bullet.h"

class accBullet : public Bullet {
public:
    Vector2 acc, vel;
    accBullet(float nowTime, float liveTime, Color col, float radius, Vector2 _pos, Vector2 _velocity, Vector2 _acc);
    float updateTime(float, Vector2);
};

#endif
