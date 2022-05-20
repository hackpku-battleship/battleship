#include "enemy.h"

Enemy::Enemy(float _hp, float _gentime, float _livetime, float _x, float _y, float _r) : hp(_hp), gentime(_gentime), livetime(_livetime), x(_x), y(_y), r(_r), dutime(0.0)
{
    // std::cerr << "livetime:" << livetime << std::endl;
}

std::vector<Bullet *> Enemy::getBullet(float nowtime, BulletManager *manager)
{
    return std::vector<Bullet *>();
}

float Enemy::getX()
{
    return x;
}

float Enemy::getY()
{
    return y;
}

float Enemy::getR()
{
    return r;
}

bool Enemy::isalive()
{
    return hp > 0 && dutime <= livetime;
}

void Enemy::hit()
{
    hp -= 1;
}