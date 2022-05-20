#ifndef SPLIT_BULLET_H
#define SPLIT_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include "basicBullet.h"
#include "bulletManager.h"
#include <bits/stdc++.h>

class splitBullet : public Bullet
{
    Vector2 velocity;
    BulletManager *creater;
    float dutime;
    float speed;

public:
    splitBullet(float nowTime, float lifeTime, Color col, float radius, Vector2 startPosition, Vector2 velocity, float speed, BulletManager *creater);
    float updateTime(float, Vector2);
};

#endif