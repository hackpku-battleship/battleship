#ifndef SPLIT_BULLET_H
#define SPLIT_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include "fishBullet.h"
#include "bulletManager.h"
#include <bits/stdc++.h>

//分裂弹，一段时间后分裂出多个不同的弹
class splitBullet : public Bullet
{
    Vector2 velocity;
    float dutime;
    float speed;
    std::vector<Bullet *> bullets;

public:
    splitBullet(float nowTime, float lifeTime, BulletManager *from, Color col, float radius, Vector2 startPosition, Vector2 velocity, std::vector<Bullet *> bullets);
    ~splitBullet();
    float updateTime(float, Vector2);
    virtual void turnBack();
};

#endif