#include "raylib.h"
#include "eldenBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

class fadingFishBullet: public fishBullet{
public:
    fadingFishBullet(float, float, Vector2, float, float, Vector2);
    void Draw();
    bool checkBox(Vector2, float);
};
fadingFishBullet::fadingFishBullet(float nowTime, float lifeTime, Vector2 startPosition, float velocity, float angleV, Vector2 startAngle):
        fishBullet(nowTime, lifeTime, startPosition, velocity, angleV, startAngle)
{
    radius=12;
}
bool fadingFishBullet::checkBox(Vector2 center, float rad){
    return CheckCollisionCircles(position, radius * (1 - (lastTime - genTime) / lifeTime), center, rad);
}
void fadingFishBullet::Draw(){
    DrawCircleV(position, radius * (1 - (lastTime - genTime) / lifeTime), PURPLE);
}

eldenBullet::eldenBullet(float nowTime, float lifeTime, Vector2 startPosition, float velocity, float angleV, BulletManager* manager, float fishV):
        fishBullet(nowTime, lifeTime, startPosition, velocity, angleV), from(manager), fishV(fishV)
{
    radius=30;
}
eldenBullet::eldenBullet(float nowTime, float lifeTime, Vector2 startPosition, float velocity, float angleV, BulletManager* manager, float fishV, Vector2 startAngle):
        fishBullet(nowTime, lifeTime, startPosition, velocity, angleV, startAngle), from(manager), fishV(fishV)
{
    radius=30;
}
float eldenBullet::updateTime(float nowTime, Vector2 playerPosition){
    if((int)(nowTime / fishV) - (int)(lastTime / fishV) >= 1){
        from -> addBullet(new fadingFishBullet(nowTime, 3, position, velocity * 2, angleV / 5, rotate(angle, PI*(1.*rand()/RAND_MAX-0.5))));
    }
    float deltaTime=fishBullet::updateTime(nowTime, playerPosition);
    return deltaTime;
}
void eldenBullet::Draw(){
    DrawCircleGradient(position.x, position.y, radius, YELLOW, Fade(YELLOW, 0.3));
}