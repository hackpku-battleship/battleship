#ifndef ACCBULLET_H
#define ACCBULLET_H

#include "bullet.h"

class accBullet : public Bullet {
public:
    Vector2 acc, pos, vel;
    float radius;
    accBullet(float nowTime, float liveTime, Vector2 _pos, Vector2 _velocity, Vector2 _acc);
    float updateTime(float, Vector2);
    void Draw();
    bool checkBox(Vector2, float);
    bool inScreen(int, int);
};

#endif
