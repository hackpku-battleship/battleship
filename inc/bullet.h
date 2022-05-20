#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include <bits/stdc++.h>

struct BulletManager;

class Bullet
{
public:
    float genTime, lifeTime, lastTime; // 子弹的生成时间
    BulletManager *from;

public:
    Bullet(float, float);
    virtual float updateTime(float, Vector2);
    bool checkAlive(float);
    virtual bool inScreen(int, int)=0;
    virtual void Draw()=0;
    virtual bool checkBox(Vector2, float)=0;
};

#endif