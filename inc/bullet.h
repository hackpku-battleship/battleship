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
    void addBullet(Bullet *x);
    void updateTime(double nowTime);
    void DrawAllBullets();
    bool checkBox(Vector2 x, double r);
    std::vector<Bullet *> getBullets();
    void setBullets(std::vector<Bullet *> v);
};

#endif