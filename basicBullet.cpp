#include "raylib.h"
#include "bullet.h"
#include "Vector2Basic.h"

basicBullet::basicBullet(float nowTime, Vector2 startPosition, Vector2 velocity):
        Bullet(nowTime),position(startPosition), velocity(velocity)
{}
float basicBullet::updateTime(float nowTime){
    float deltaTime=Bullet::updateTime(nowTime);
    position = position + deltaTime * velocity;
    return deltaTime;
}
void basicBullet::Draw(){
    DrawCircleV(position, 5, RED);
}
bool basicBullet::checkBox(){
    return 0;
}