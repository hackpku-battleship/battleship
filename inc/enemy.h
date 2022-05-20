#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "bullet.h"
#include "basicBullet.h"
#include "fishBullet.h"
#include "splitBullet.h"
#include "bulletManager.h"

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

class EnemyManager
{
public:
    std::vector<Enemy *> enemys;
    void addEnemy(Enemy *pe);
    std::vector<Bullet *> updateTime(float nowTime, BulletManager *manager);
    std::vector<Enemy *> getEnemys();
    void setEnemys(std::vector<Enemy *>);
    void draw();
};

class SimpleEnemy : public Enemy
{
    float rotatep;

public:
    SimpleEnemy(float _hp, float _genTime, float livetime, float _x, float _y, float _r);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager);
    void draw();
};

class DEnemy : public Enemy
{
public:
    DEnemy(float _hp, float _genTime, float livetime, float _x, float _y, float _r);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager);
    void draw();
};
#endif