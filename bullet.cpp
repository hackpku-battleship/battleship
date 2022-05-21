#include "raylib.h"
#include "bullet.h"
#include "player.h"
#include "bulletManager.h"

Bullet::Bullet(float nowTime, float lifeTime, BulletManager* from, Color _col, float _radius, Vector2 _pos): 
genTime(nowTime), lifeTime(lifeTime), lastTime(nowTime), col(_col), radius(_radius), pos(_pos), from(from){}

float Bullet::updateTime(float nowTime, Vector2 playerPosition)
{
    float delta = nowTime - lastTime;
    lastTime = nowTime;
    return delta;
}

bool Bullet::checkAlive(float nowTime)
{
    // std::cerr<<nowTime<<' '<<genTime+lifeTime<<std::endl;
    return genTime + lifeTime > nowTime;
}
Bullet::~Bullet(){}
void Bullet::Draw(){
    DrawCircleV(pos, radius, col);
}
bool Bullet::checkBox(Vector2 center, float rad)
{
    return CheckCollisionCircles(pos, radius, center, rad);
}
bool Bullet::checkProt(Vector2 p, float r)
{
    return CheckCollisionCircleRec(pos, radius, PROT_REC);
}
bool Bullet::inScreen(int H, int W)
{
    return 0 <= pos.x && pos.x < H && 0 <= pos.y && pos.y < W;
}
void Bullet::Move(Vector2 dir)
{
    pos.x = pos.x + dir.x;
    pos.y = pos.y + dir.y;
}