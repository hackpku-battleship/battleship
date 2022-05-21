#ifndef BASIC_BULLET_H
#define BASIC_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include <bits/stdc++.h>

class basicBullet: public Bullet{
    Vector2 position, velocity;
    float radius;
public:
    basicBullet(float, float, Vector2, Vector2);
    float updateTime(float, Vector2);
    void Draw();
    bool checkBox(Vector2, float);
    bool inScreen(int, int);
};


#endif