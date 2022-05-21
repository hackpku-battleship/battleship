#ifndef BAKADIRECT_H
#define BAKADIRECT_H

#include "enemy.h"

class bakaDirect : public Enemy {
public:
    Vector2 vel;
    bakaDirect(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename, Vector2 vel);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager, Vector2 playerPosition);
};

#endif