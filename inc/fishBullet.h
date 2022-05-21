#ifndef FISH_BULLET_H
#define FISH_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include <bits/stdc++.h>

//追踪弹，追踪玩家位置
class fishBullet: public Bullet{
protected:
    Vector2 angle;
    float velocity, angleV;
    bool fade;
public:
    fishBullet(float nowTime, float lifeTime, BulletManager* from, Color col, float radius, Vector2 startPosition, float velocity, float angleV);
    fishBullet(float nowTime, float lifeTime, BulletManager* from, Color col, float radius, Vector2 startPosition, float velocity, float angleV, Vector2 startAngle, bool fade=false);
    virtual ~fishBullet();
    float updateTime(float, Vector2);
    void Draw();
    virtual void turnBack();
};


#endif