#ifndef SHOTSIMPLETRACEENEMY_H
#define SHOTSIMPLETRACEENEMY_H

#include "enemy.h"

class shotSimpleTraceEnemy : public Enemy {
    float fastv, slowv;
    int flag;
    Vector2 f;
public:
    shotSimpleTraceEnemy(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename, float fastv, float slowv);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager, Vector2 playerPosition);
};

#endif