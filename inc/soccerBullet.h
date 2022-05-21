#ifndef SOCCER_BULLET_H
#define SOCCER_BULLET_H

#include "raylib.h"
#include "bullet.h"
#include <bits/stdc++.h>

//足球弹，先展示警告，然后延迟射出
class soccerBullet: public Bullet{
    Texture2D tex;
    float delayTime, rotation, angV;
    Vector2 velocity, endPoint;
public:
    soccerBullet(float nowTime, float liveTime, BulletManager* from, Color col, float radius, Vector2 startPos, float delayTime, Vector2 endPoint, char* imgPath);
    float updateTime(float nowTime, Vector2 playerPosition);
    void Draw();
};


#endif