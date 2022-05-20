#include "accbullet.h"
#include "Vector2Basic.h"

accBullet::accBullet(float nowTime, float liveTime, Vector2 _pos, Vector2 velocity, Vector2 _acc):
        Bullet(nowTime, liveTime), pos(_pos), vel(velocity), acc(_acc) {
            radius = 5;
        }

float accBullet::updateTime(float nowTime, Vector2 playerpos) {
    float delta = Bullet::updateTime(nowTime, playerpos);
    vel = vel + delta * acc;
    pos = pos + delta * vel;
    return delta;
}

void accBullet::Draw(){
    DrawCircleV(pos, radius, BLACK);
}
bool accBullet::checkBox(Vector2 center, float rad){
    return CheckCollisionCircles(pos, radius, center, rad);
}
bool accBullet::inScreen(int H, int W){
    return 0<=pos.x && pos.x<H && 0<=pos.y && pos.y<W;
}