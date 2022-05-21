#include "turningTraceBullet.h"
#include "Vector2Basic.h"

turningTraceBullet::turningTraceBullet(float nowTime, float liveTime, BulletManager* from, Color col, float radius, 
        Vector2 pos, Vector2 vel1, float vel2, float _turningtime) :
        Bullet(nowTime, liveTime, from, col, radius, pos), v1(vel1), v2(vel2), turningtime(_turningtime),
        isgetplayerpos(false){}
float turningTraceBullet::updateTime(float nowTime, Vector2 playerpos) {
    float delta = Bullet::updateTime(nowTime, playerpos);
    if (nowTime - genTime <= turningtime) pos = pos + delta * v1;
    else {
        if (isgetplayerpos == false) {
            f = normalize(playerpos - pos);
            isgetplayerpos = true;
        }
        pos = pos + delta * v2 * f;
    }
    return delta;
}