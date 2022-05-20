#include "enemy.h"

Enemy::Enemy(float _hp, float _gentime, float _x, float _y, float _r) : 
    hp(_hp), gentime(_gentime), x(_x), y(_y), r(_r), dutime(0.0){
}

std::vector<Bullet> Enemy::getBullet(float nowtime) {
    return std::vector<Bullet>();
}

float Enemy::getX() {
    return x;
}

float Enemy::getY() {
    return y;
}

float Enemy::getR() {
    return r;
}

SimpleEnemy::SimpleEnemy(float _hp, float _gentime, float _x, float _y, float _r):
    Enemy(_hp, _gentime, _x, _y, _r) {}

std::vector<Bullet> SimpleEnemy::getBullet(float nowTime) {
    float dtime = nowTime - gentime;
    std::vector<Bullet> ret;
    if (dutime <= 0 && dtime >= 0.5) {
        ret.push_back((basicBullet)())
    }
    dutime = dtime;
}