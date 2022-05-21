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
    float radius;
    Color col;
    Vector2 pos;

public:
    Bullet(float nowTime, float liveTime, Color col, float radius, Vector2 pos);
    virtual ~Bullet();
    virtual float updateTime(float, Vector2);
    bool checkAlive(float);
    bool inScreen(int, int);
    void Draw();
    bool checkBox(Vector2, float);
    bool checkProt(Vector2, float);
    void Move(Vector2 dir);
};

// bullet manager

#endif