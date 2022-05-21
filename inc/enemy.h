#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "utils.h"
#include "bullet.h"
#include "basicBullet.h"
#include "fishBullet.h"
#include "eldenBullet.h"
#include "splitBullet.h"
#include "bulletManager.h"
#include "accbullet.h"
#include "turningbullet.h"
#include "tracebullet.h"
#include "turningTraceBullet.h"

class Enemy
{
public:
    float hp;
    float gentime, dutime, livetime;
    Vector2 pos;
    float r;
    Texture2D tex;
    Enemy(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename);
    virtual std::vector<Bullet *> getBullet(float nowTime, BulletManager *manager, Vector2 playerPosition);
    float getX();
    float getY();
    float getR();
    void draw();
    bool isalive();
    void hit();
    ~Enemy();
};
#endif