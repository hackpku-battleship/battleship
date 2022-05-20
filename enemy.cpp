#include "enemy.h"

Enemy::Enemy(float _hp, float _gentime, float _x, float _y, float _r) : 
    hp(_hp), gentime(_gentime), x(_x), y(_y), r(_r), dutime(0.0){
}

std::vector<Bullet*> Enemy::getBullet(float nowtime) {
    return std::vector<Bullet*>();
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