#ifndef BASIC_BULLET_H
#define BASIC_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include <bits/stdc++.h>

struct BulletManager;

//普通匀速弹，指定初始方向和速度
class basicBullet: public Bullet{
    Vector2 velocity;
public:
    basicBullet(float nowTime, float liveTime, Color col, float radius, Vector2 _pos, Vector2 _velocity);
    float updateTime(float, Vector2);
    void Draw();
    bool checkBox(Vector2, float);
    bool inScreen(int, int);
};


#endif