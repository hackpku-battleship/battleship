#include "turningbullet.h"
#include "Vector2Basic.h"

TurningBullet::TurningBullet(float nowTime, float liveTime, BulletManager* from, Color col, 
                            float radius, Vector2 _pos, Vector2 _vel1, 
                            Vector2 _vel2, float _turnTime) :
    Bullet(nowTime, liveTime, from, col, radius, _pos), vel1(_vel1), vel2{_vel2}, turntime(_turnTime) {
    }
float TurningBullet::updateTime(float nowTime, Vector2 playerpos) {
    float delta = Bullet::updateTime(nowTime, playerpos);
    if (nowTime - genTime <= turntime) pos = pos + delta * vel1;
    else pos = pos + delta * vel2;
    return delta;
}
void TurningBullet::Draw() {
    DrawCircleV(pos, radius, GRAY);
}
bool TurningBullet::checkBox(Vector2 center, float rad) {
    return CheckCollisionCircles(pos, radius, center, rad);
}
bool TurningBullet::inScreen(int H, int W) {
    return 0<=pos.x && pos.x<H && 0<=pos.y && pos.y<W;
}