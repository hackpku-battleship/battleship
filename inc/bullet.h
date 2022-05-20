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
    virtual float updateTime(float);
    bool checkAlive(float);
    virtual void Draw() = 0;
    virtual bool checkBox(Vector2, float) = 0;
};

class basicBullet : public Bullet
{
    Vector2 position, velocity;
    float radius;

public:
    basicBullet(float, float, Vector2, Vector2);
    float updateTime(float);
    void Draw();
    bool checkBox(Vector2, float);
};

// bullet manager
struct BulletManager
{
    std::vector<Bullet *> bullets;
    void addBullet(Bullet *x) { bullets.push_back(x); }
    void updateTime(double nowTime)
    {
        for (int i = 0; i < bullets.size(); ++i)
        {
            if (!bullets[i]->checkAlive(nowTime))
            {
                bullets.erase(bullets.begin() + i);
                --i;
            }
            else
                bullets[i]->updateTime(nowTime);
        }
    }
    void DrawAllBullets()
    {
        for (Bullet *p : bullets)
        {
            p->Draw();
        }
    }
    bool checkBox(Vector2 x, double r)
    {
        for (Bullet *p : bullets)
            if (p->checkBox(x, r))
                return true;
        return false;
    }
    bool checkHit(Vector2 x, double r)
    {
        bool ret = false;
        std::vector<Bullet *> rem;
        for (Bullet *p : bullets)
            if (p->checkBox(x, r))
                ret = true;
            else
                rem.push_back(p);
        bullets = rem;
        return ret;
    }
};

#endif