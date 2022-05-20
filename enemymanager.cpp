#include "enemy.h"

std::vector<Bullet *> EnemyManager::updateTime(float nowTime)
{
    std::vector<Bullet *> ret;
    for (int i = 0; i < enemys.size(); i++)
    {
        auto _a = enemys[i]->getBullet(nowTime);
        if (enemys[i]->isalive() == 0)
            enemys.erase(enemys.begin() + i);
        else
            ret.insert(ret.end(), _a.begin(), _a.end());
    }
    return ret;
}

void EnemyManager::addEnemy(Enemy *pe)
{
    enemys.push_back(pe);
}

void EnemyManager::draw()
{
    for (auto it : enemys)
        it->draw();
    return;
}

std::vector<Enemy *> EnemyManager::getEnemys()
{
    return enemys;
}

void EnemyManager::setEnemys(std::vector<Enemy *> v)
{
    enemys = v;
}