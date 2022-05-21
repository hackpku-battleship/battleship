#include "raylib.h"
#include "bulletManager.h"
#include "soccerBullet.h"
#include "Vector2Basic.h"
#include <bits/stdc++.h>

soccerBullet::soccerBullet(float nowTime, float liveTime, BulletManager* from, Color col, float radius, Vector2 startPos, float delayTime, Vector2 endPoint):
        Bullet(nowTime, liveTime, from, col, radius, startPos), delayTime(delayTime), endPoint(endPoint), angV(720), rotation(0),
        velocity((1.0f / (liveTime - delayTime)) * (endPoint - startPos)){
            tex = LoadTexture("source/soccer-ball.png");
        }

float soccerBullet::updateTime(float nowTime, Vector2 playerPosition){
    float _deltaTime=0;
    if(lastTime < genTime + delayTime) _deltaTime = delayTime - (lastTime - genTime);
    float deltaTime=Bullet::updateTime(nowTime, playerPosition);
    _deltaTime = std::max(deltaTime - _deltaTime, 0.0f);
    if(nowTime < genTime + delayTime) angV = 720 * (1 - (nowTime - genTime) / delayTime);
    else angV = std::max<float>(180, (nowTime - genTime - delayTime) *360 * 4);
    pos = pos + _deltaTime * velocity;
    rotation += angV * deltaTime;
    return deltaTime;
}
void soccerBullet::Draw(){
    if(lastTime < genTime + delayTime && int((genTime + delayTime - lastTime) / 0.3) % 2)
        DrawLineEx(pos, endPoint, radius*2, Fade(RED, 0.2));
    const static Rectangle source = {0, 0, 512, 512};
    const static Vector2 origin = {radius, radius};
    Rectangle dest = {pos.x, pos.y, radius*2, radius*2};
    DrawTexturePro(tex, source, dest, origin, rotation, WHITE);
}