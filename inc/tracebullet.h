#ifndef TRACEBULLET_H
#define TRACEBULLET_H

#include "bullet.h"
//跟踪弹，以生成时玩家的位置为方向
class traceBullet : public Bullet {
    Vector2 f;
    bool isgetplayerpos;
    float vel;
public:
    traceBullet(float nowTime, float liveTime, BulletManager* from, Color col, float radius, Vector2 pos, float vel);
    virtual float updateTime(float, Vector2);
};

#endif