#include "raylib.h"
#include "bullet.h"

Bullet::Bullet(float nowTime, float lifeTime): genTime(nowTime), lifeTime(lifeTime){}
float Bullet::updateTime(float nowTime){
    float delta=nowTime-genTime;
    return delta;
}
bool Bullet::checkAlive(float nowTime){
    std::cerr<<nowTime<<' '<<genTime+lifeTime<<std::endl;
    return genTime+lifeTime>nowTime;
}