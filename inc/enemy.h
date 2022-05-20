#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "bullet.h"

class Enemy {
    float hp;
    float gentime, dutime;
    float x, y, r;
public:
    Enemy(float _hp, float _genTime, float _x, float _y, float _r);
    virtual std::vector<Bullet> getBullet(float nowTime);
    float getX();
    float getY();
    float getR();
};

class SimpleEnemy : Enemy {
public:
    SimpleEnemy(float _hp, float _genTime, float _x, float _y, float _r);
};
#endif