#ifndef ELDEN_BULLET_H
#define ELDEN_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include "fishBullet.h"
#include "BulletManager.h"
#include <bits/stdc++.h>


class eldenBullet: public fishBullet{
    float fishV; // 每fishV秒生成1个fish弹
public:
    eldenBullet(float nowTime, float lifeTime, BulletManager* from, Color col, float radius, Vector2 startPosition, float velocity, float angleV, float fishV);
    eldenBullet(float nowTime, float lifeTime, BulletManager* from, Color col, float radius, Vector2 startPosition, float velocity, float angleV, float fishV, Vector2 startAngle);
    float updateTime(float, Vector2);
    virtual void turnBack();
};


#endif