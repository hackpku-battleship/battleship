#include "accbullet.h"
#include "Vector2Basic.h"

accBullet::accBullet(float nowTime, float liveTime, BulletManager* from, Color col, float radius, Vector2 pos, Vector2 _velocity, Vector2 _acc):
        Bullet(nowTime, liveTime, from, col, radius, pos), vel(_velocity), acc(_acc) {}

float accBullet::updateTime(float nowTime, Vector2 playerpos) {
    float delta = Bullet::updateTime(nowTime, playerpos);
    vel = vel + delta * acc;
    pos = pos + delta * vel;
    return delta;
}
void accBullet::turnBack(){
    vel = (-1) * vel;
}
