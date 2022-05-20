#ifndef BAKADIRECT_H
#define BAKADIRECT_H

#include "enemy.h"

class bakaDirect : public Enemy {
public:
    bakaDirect(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager);
};

#endif