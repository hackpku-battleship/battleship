#ifndef SPINENEMY_H
#define SPINENEMY_H

#include "enemy.h"

class spinEnemy : public Enemy {
public:
    Vector2 vel;
    float spinrate;
    float lastalpha;
    spinEnemy(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename, Vector2 vel, float spinrate);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager);
};

#endif