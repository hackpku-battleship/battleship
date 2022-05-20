#ifndef SPLIT_BULLET_H
#define SPLIT_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include "basicBullet.h"
#include "bulletManager.h"
#include <bits/stdc++.h>

class splitBullet : public Bullet
{
    Vector2 position, velocity;
    float radius;
    BulletManager *creater;
    float dutime;
    float speed;

public:
    splitBullet(float, float, Vector2, Vector2, float, BulletManager *);
    float updateTime(float, Vector2);
    void Draw();
    bool checkBox(Vector2, float);
    bool inScreen(int, int);
};

#endif