#ifndef ELDEN_BULLET_H
#define ELDEN_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include "fishBullet.h"
#include "BulletManager.h"
#include <bits/stdc++.h>


class eldenBullet: public fishBullet{
    BulletManager* from;
    float fishV; // 每fishV秒生成1个fish弹
public:
    eldenBullet(float, float, Vector2, float, float, BulletManager*, float);
    eldenBullet(float, float, Vector2, float, float, BulletManager*, float, Vector2);
    float updateTime(float, Vector2);
    void Draw();
};


#endif