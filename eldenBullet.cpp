#include "raylib.h"
#include "eldenBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

eldenBullet::eldenBullet(float nowTime, float lifeTime, BulletManager* from, Color col, float radius, Vector2 startPosition, float velocity, float angleV, float fishV):
    fishBullet(nowTime, lifeTime, from, col, radius, startPosition, velocity, angleV), fishV(fishV){}
eldenBullet::eldenBullet(float nowTime, float lifeTime, BulletManager* from, Color col, float radius, Vector2 startPosition, float velocity, float angleV, float fishV, Vector2 startAngle):
    fishBullet(nowTime, lifeTime, from, col, radius, startPosition, velocity, angleV, startAngle), fishV(fishV){}
    
float eldenBullet::updateTime(float nowTime, Vector2 playerPosition){
    if((int)(nowTime / fishV) - (int)(lastTime / fishV) >= 1){
        from -> addBullet(new fishBullet(nowTime, 3, from, RED, 10, pos, velocity * 2, angleV / 5, rotate(angle, PI*(1.*rand()/RAND_MAX-0.5)), true));
    }
    float deltaTime=fishBullet::updateTime(nowTime, playerPosition);
    return deltaTime;
}
void eldenBullet::turnBack(){
    fishBullet::turnBack();
    fishV = 1e18;
}