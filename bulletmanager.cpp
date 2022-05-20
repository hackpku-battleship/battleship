#include "bullet.h"

void BulletManager::addBullet(Bullet *x) { bullets.push_back(x); }
void BulletManager::updateTime(double nowTime)
{
    for (int i = 0; i < bullets.size(); ++i)
    {
        if (!bullets[i]->checkAlive(nowTime))
        {
            bullets.erase(bullets.begin() + i);
            --i;
        }
        else
            bullets[i]->updateTime(nowTime);
    }
}
void BulletManager::DrawAllBullets()
{
    for (Bullet *p : bullets)
    {
        p->Draw();
    }
}
bool BulletManager::checkBox(Vector2 x, double r)
{
    for (Bullet *p : bullets)
        if (p->checkBox(x, r))
            return true;
    return false;
}
std::vector<Bullet *> BulletManager::getBullets()
{
    return bullets;
}
void BulletManager::setBullets(std::vector<Bullet *> v)
{
    bullets = v;
}