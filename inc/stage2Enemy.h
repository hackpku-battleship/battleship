#ifndef STAGE2ENEMY_H
#define STAGE2ENEMY_H

#include "enemy.h"

class stage2Enemy : public Enemy {
public:
    stage2Enemy(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename);
    std::vector<Bullet *> getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition);
};

#endif