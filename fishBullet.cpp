#include "raylib.h"
#include "fishBullet.h"
#include "Vector2Basic.h"
#include "bulletManager.h"
#include <bits/stdc++.h>

fishBullet::~fishBullet(){}
fishBullet::fishBullet(float nowTime, float lifeTime, BulletManager*from, Color col, float radius, Vector2 startPosition, float velocity, float angleV):
        Bullet(nowTime, lifeTime, from, col, radius, startPosition), velocity(velocity), angleV(angleV), fade(false)
{
    angle={0, velocity};
}
fishBullet::fishBullet(float nowTime, float lifeTime, BulletManager*from, Color col, float radius, Vector2 startPosition, float velocity, float angleV, Vector2 startAngle, bool fade):
        fishBullet(nowTime, lifeTime, from, col, radius, startPosition, velocity, angleV)
{
    angle=(velocity/norm(startAngle)) * startAngle;
    this->fade=fade;
}
float fishBullet::updateTime(float nowTime, Vector2 playerPosition){
    float deltaTime=Bullet::updateTime(nowTime, playerPosition);
    Vector2 d = playerPosition - pos;
    float ang = std::min<float>(angleV ,acos((1./norm(d)) * angle * d)) * deltaTime;
    // norm(angle) = 1
    angle = rotate(angle, (angle % d > 0 ? 1 : -1) * ang);
    pos = pos + deltaTime * angle;
    return deltaTime;
}
void fishBullet::Draw(){
    DrawCircleV(pos, fade ? radius * (1 - (lastTime - genTime) / lifeTime) : radius, col);
}
void fishBullet::turnBack(){
    angleV = 0;
    angle = (-1) * angle;
}