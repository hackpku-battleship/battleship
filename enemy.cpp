#include "enemy.h"

Enemy::Enemy(float _hp, float _gentime, float _livetime, float _x, float _y, float _r, char* filename) :
    hp(_hp), gentime(_gentime), livetime(_livetime), x(_x), y(_y), r(_r), dutime(0.0)
{
    tex = LoadTexture(filename);
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

void Enemy::draw() {
    int frameWidth = tex.width;
    int frameHeight = tex.height;
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    Rectangle destRec = { x - r, y - r, r*2.0f, r*2.0f };
    Vector2 origin = {r, r};
    DrawTexturePro(tex, sourceRec, destRec, origin, 0.0, WHITE);
    //DrawCircleV((Vector2){x, y}, r, PURPLE);
}