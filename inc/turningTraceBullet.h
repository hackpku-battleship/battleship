#ifndef TURNINGTRACEBULLET_H
#define TURNINGTRACEBULLET_H

#include "bullet.h"
//跟踪弹，先以一个方向射出，一段时间后转向玩家当时的位置
class turningTraceBullet : public Bullet {
    Vector2 v1, f;
    float v2;
    float turningtime;
    bool isgetplayerpos;
public:
    turningTraceBullet(float nowTime, float liveTime, BulletManager* from, Color col, float radius, 
        Vector2 pos, Vector2 vel1, float vel2, float turningtime);
    float updateTime(float, Vector2);
};

#endif
