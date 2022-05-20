#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "utils.h"
#include "bullet.h"
#include "basicBullet.h"
#include "fishBullet.h"
#include "splitBullet.h"
#include "bulletManager.h"
#include "accbullet.h"
#include "turningbullet.h"

class Enemy
{
public:
    float hp;
    float gentime, dutime, livetime;
    float x, y, r;
    Enemy(float _hp, float _genTime, float livetime, float _x, float _y, float _r);
    virtual std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager);
    float getX();
    float getY();
    float getR();
    virtual void draw() {}
    bool isalive();
    void hit();
};
#endif