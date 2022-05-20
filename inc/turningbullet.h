#ifndef TURNINGBULLET_H
#define TURNINGBULLET_H

#include "bullet.h"

class TurningBullet : public Bullet {
public:
    Vector2 pos, vel1, vel2;
    float turntime, radius;
    TurningBullet(float nowTime, float liveTime, Vector2 pos, Vector2 vel1, Vector2 vel2, float turnTime);
    float updateTime(float, Vector2);
    void Draw();
    bool checkBox(Vector2, float);
    bool inScreen(int, int);
};

#endif