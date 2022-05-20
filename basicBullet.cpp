#include "raylib.h"
#include "basicBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

basicBullet::basicBullet(float nowTime, float lifeTime, Vector2 startPosition, Vector2 velocity):
        Bullet(nowTime, lifeTime),position(startPosition), velocity(velocity)
{
    radius=5;
}
float basicBullet::updateTime(float nowTime, Vector2 playerPosition){
    float deltaTime=Bullet::updateTime(nowTime, playerPosition);
    position = position + deltaTime * velocity;
    return deltaTime;
}
void basicBullet::Draw(){
    DrawCircleV(position, radius, RED);
}
bool basicBullet::checkBox(Vector2 center, float rad){
    return CheckCollisionCircles(position, radius, center, rad);
}
bool basicBullet::inScreen(int H, int W){
    return 0<=position.x && position.x<H && 0<=position.y && position.y<W;
}