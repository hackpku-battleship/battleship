#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "enemy.h"
#include "bullet.h"
#include <vector>

class EnemyManager
{
public:
    std::vector<Enemy *> enemys;
    void addEnemy(Enemy *pe)
    {
        enemys.push_back(pe);
    }
    std::vector<Bullet *> updateTime(float nowTime, BulletManager *manager);
    void draw();
    std::vector<Enemy *> getEnemys();
    void setEnemys(std::vector<Enemy *>);
};

#endif