#include "raylib.h"
#include "bullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

basicBullet::basicBullet(float nowTime, float lifeTime, Vector2 startPosition, Vector2 velocity):
        Bullet(nowTime, lifeTime),position(startPosition), velocity(velocity)
{
    radius=5;
}
float basicBullet::updateTime(float nowTime){
    float deltaTime=Bullet::updateTime(nowTime);
    position = position + deltaTime * velocity;
    return deltaTime;
}
void basicBullet::Draw(){
    DrawCircleV(position, 5, RED);
}
bool basicBullet::checkBox(Vector2 center, float rad){
    return CheckCollisionCircles(position, radius, center, rad);
}