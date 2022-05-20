#ifndef TURNINGBULLET_H
#define TURNINGBULLET_H

#include "bullet.h"

class TurningBullet : public Bullet {
public:
    Vector2 vel1, vel2;
    float turntime;
    TurningBullet(float nowTime, float liveTime, Color col, float radius, Vector2 _pos, Vector2 _vel1, Vector2 _vel2, float _turnTime);
    float updateTime(float, Vector2);
    void Draw();
    bool checkBox(Vector2, float);
    bool inScreen(int, int);
};

#endif