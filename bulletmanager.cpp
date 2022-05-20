#include "bulletManager.h"

void BulletManager::addBullet(Bullet *x) { bullets.push_back(x); }
void BulletManager::updateTime(double nowTime, int Height, int Weight, Vector2 playerPosition)
{
    for (int i = 0; i < bullets.size(); ++i)
    {
        if (!bullets[i]->inScreen(Height, Weight) || !bullets[i]->checkAlive(nowTime))
        {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            --i;
        }
        else
            bullets[i]->updateTime(nowTime, playerPosition);
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