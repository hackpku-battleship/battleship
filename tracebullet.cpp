#include "tracebullet.h"
#include "Vector2Basic.h"

traceBullet::traceBullet(float nowTime, float liveTime, Color col, float radius, 
        Vector2 pos, float vel) : isgetplayerpos(false), vel(vel),
        Bullet(nowTime, liveTime, col, radius, pos) {}

float traceBullet::updateTime(float nowTime, Vector2 _playerpos){
    float delta = Bullet::updateTime(nowTime, _playerpos);
    if (isgetplayerpos == false) {
        f = normalize(_playerpos - pos);
        isgetplayerpos = true;
    }
    pos = pos + vel * f;
    return delta;
}