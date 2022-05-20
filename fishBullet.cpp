#include "raylib.h"
#include "fishBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

fishBullet::fishBullet(float nowTime, float lifeTime, Color col, float radius, Vector2 startPosition, float velocity, float angleV):
        Bullet(nowTime, lifeTime, col, radius, startPosition), velocity(velocity), angleV(angleV)
{
    angle={0, velocity};
}
float fishBullet::updateTime(float nowTime, Vector2 playerPosition){
    float deltaTime=Bullet::updateTime(nowTime, playerPosition);
    Vector2 d = playerPosition - pos;
    float ang = std::min<float>(angleV ,acos((1./norm(d)) * angle * d));
    // norm(angle) = 1
    angle = rotate(angle, (angle % d > 0 ? 1 : -1) * ang);
    pos = pos + deltaTime * angle;
    return deltaTime;
}