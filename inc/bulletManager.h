#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "raylib.h"
#include "bullet.h"
#include <bits/stdc++.h>

struct BulletManager
{
    std::vector<Bullet *> bullets;
    void addBullet(Bullet *x);
    void updateTime(double nowTime, int Height, int Weight, Vector2 playerPosition);
    void DrawAllBullets();
    bool checkBox(Vector2 x, double r);
    std::vector<Bullet *> getBullets();
    void setBullets(std::vector<Bullet *> v);
    bool isEmpty();
};

#endif