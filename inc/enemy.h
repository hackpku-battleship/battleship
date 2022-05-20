#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "bullet.h"
#include "basicBullet.h"
#include "fishBullet.h"

class Enemy {
public:
    float hp;
    float gentime, dutime, livetime;
    float x, y, r;
    Enemy(float _hp, float _genTime, float livetime, float _x, float _y, float _r);
    virtual std::vector<Bullet*> getBullet(float nowTime);
    float getX();
    float getY();
    float getR();
    virtual void draw() {}
    bool isalive();
};

class EnemyManager {
public:
    std::vector<Enemy*> enemys;
    void addEnemy(Enemy* pe) {
        enemys.push_back(pe);
    }
    std::vector<Bullet*> updateTime(float nowTime);
    void draw();
};

class SimpleEnemy : public Enemy {
    float rotatep;
public:
    SimpleEnemy(float _hp, float _genTime, float livetime, float _x, float _y, float _r);
    std::vector<Bullet*> getBullet(float nowTime);
    void draw();
};

class DEnemy:public Enemy {
public:
    DEnemy(float _hp, float _genTime, float livetime, float _x, float _y, float _r);
    std::vector<Bullet*> getBullet(float nowTime);
    void draw();
};
#endif