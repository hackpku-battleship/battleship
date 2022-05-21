#include "raylib.h"
#include "fishBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

fishBullet::fishBullet(float nowTime, float lifeTime, Vector2 startPosition, float velocity, float angleV):
        Bullet(nowTime, lifeTime),position(startPosition), velocity(velocity), angleV(angleV)
{
    radius=6;
    angle={0, velocity};
}
fishBullet::fishBullet(float nowTime, float lifeTime, Vector2 startPosition, float velocity, float angleV, Vector2 startAngle):
        Bullet(nowTime, lifeTime),position(startPosition), velocity(velocity), angleV(angleV)
{
    radius=6;
    angle=(velocity/norm(startAngle)) * startAngle;
}
float fishBullet::updateTime(float nowTime, Vector2 playerPosition){
    float deltaTime=Bullet::updateTime(nowTime, playerPosition);
    Vector2 d = playerPosition - position;
    float ang = std::min<float>(angleV ,acos((1./norm(d)) * angle * d)) * deltaTime;
    // norm(angle) = 1
    angle = rotate(angle, (angle % d > 0 ? 1 : -1) * ang);
    position = position + deltaTime * angle;
    return deltaTime;
}
void fishBullet::Draw(){
    DrawCircleV(position, radius, PURPLE);
}
bool fishBullet::checkBox(Vector2 center, float rad){
    return CheckCollisionCircles(position, radius, center, rad);
}
bool fishBullet::inScreen(int H, int W){
    return -30<=position.x && position.x<=H+30 && -30<=position.y && position.y<=W+30;
}