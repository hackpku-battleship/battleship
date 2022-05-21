#ifndef TURNINGBULLET_H
#define TURNINGBULLET_H

#include "bullet.h"
//转向弹，一段时间之后速度方向改变，需要传入两个速度
class TurningBullet : public Bullet {
public:
    Vector2 vel1, vel2;
    float turntime;
    TurningBullet(float nowTime, float liveTime, BulletManager* from, Color col, float radius, Vector2 _pos, Vector2 _vel1, Vector2 _vel2, float _turnTime);
    float updateTime(float, Vector2);
};

#endif