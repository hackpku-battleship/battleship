#include "raylib.h"
#include "bulletManager.h"
#include "basicBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

basicBullet::basicBullet(float nowTime, float liveTime, BulletManager* from, Color col, float radius, Vector2 _pos, Vector2 _velocity):
        Bullet(nowTime, liveTime, from, col, radius, _pos), velocity(_velocity){}

float basicBullet::updateTime(float nowTime, Vector2 playerPosition){
    float deltaTime=Bullet::updateTime(nowTime, playerPosition);
    pos = pos + deltaTime * velocity;
    return deltaTime;
}
void basicBullet::turnBack(){
    velocity = (-1) * velocity;
}