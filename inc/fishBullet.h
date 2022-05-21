#ifndef FISH_BULLET_H
#define FISH_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include <bits/stdc++.h>

class fishBullet: public Bullet{
protected:
    Vector2 position, angle;
    float radius, velocity, angleV;
public:
    fishBullet(float, float, Vector2, float, float);
    fishBullet(float, float, Vector2, float, float, Vector2);
    float updateTime(float, Vector2);
    void Draw();
    virtual bool checkBox(Vector2, float);
    bool inScreen(int, int);
};


#endif