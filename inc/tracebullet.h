#ifndef TRACEBULLET_H
#define TRACEBULLET_H

#include "bullet.h"

class traceBullet : public Bullet {
    Vector2 f;
    bool isgetplayerpos;
    float vel;
public:
    traceBullet(float nowTime, float liveTime, BulletManager* from, Color col, float radius, Vector2 pos, float vel);
    virtual float updateTime(float, Vector2);
};

#endif