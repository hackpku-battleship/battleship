#include "raylib.h"
#include "basicBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

basicBullet::basicBullet(float nowTime, float liveTime, Color col, float radius, Vector2 _pos, Vector2 _velocity):
        Bullet(nowTime, liveTime, col, radius, _pos), velocity(_velocity){}

float basicBullet::updateTime(float nowTime, Vector2 playerPosition){
    float deltaTime=Bullet::updateTime(nowTime, playerPosition);
    pos = pos + deltaTime * velocity;
    return deltaTime;
}