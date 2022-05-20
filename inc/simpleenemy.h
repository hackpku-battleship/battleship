#ifndef SIMPLE_ENEMY_H
#define SIMPLE_ENEMY_H

#include "enemy.h"

class SimpleEnemy : public Enemy {
public:
    SimpleEnemy(float _hp, float _genTime, float _x, float _y, float _r);
    std::vector<Bullet> getBullet(float nowTime);
};

#endif