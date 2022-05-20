#include "raylib.h"
#include "bullet.h"

Bullet::Bullet(float nowTime){
    genTime = nowTime;
}
float Bullet::updateTime(float nowTime){
    float delta=nowTime-genTime;
    genTime=nowTime;
    return delta;
}