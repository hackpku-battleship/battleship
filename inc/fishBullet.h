#ifndef FISH_BULLET_H
#define FISH_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include <bits/stdc++.h>

struct BulletManager;

//追踪弹，追踪玩家位置
class fishBullet: public Bullet{
    Vector2 angle;
    float velocity, angleV;
public:
    fishBullet(float nowTime, float lifeTime, Color col, float radius, Vector2 startPosition, float velocity, float angleV);
    float updateTime(float, Vector2);
};


#endif