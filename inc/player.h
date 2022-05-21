#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <list>
#include "bulletManager.h"
#define MAXLP 5 //最大技能释放次数
#define PROT_LIMITTIME 5
#define PROT_REC {p.x - r - 25, p.y - r - 10, 60, 5}
#define BOOMSCOPE 200
#define LASTOFRING 0.2
#define FOOTBALLSP 300
#define BALLCD 0.5

class PlayerHPBar
{
    float x, y, radius, delta;

public:
    PlayerHPBar(float x, float y, float radius, float delta);
    void Draw(int hp);
};

class Prot {
    float StartTime, LimitTime;
public:
    Prot(float _StartTime);
    void Draw(Vector2 p, float r);
    void Hit();
    bool Check(float nowTime);
};

class Atk {
    std::list<Vector2> Ps;
    float R, Speed;
public:
    Atk(float _R);
    void Draw();
    void Move(float deltatime);
    void HitBullet(BulletManager * enemyBullets);
    void HitEnemy();
    void Check(int screenWidth, int screenHeight);
    void Add(Vector2);
};

class Player
{
    Vector2 position;
    float radius;
    int hp;
    const float speed;
    const float minY;
    const float maxX;
    const float hitlessTime;
    const float lowspeed;
    float lastHitTime = -1e300;
    bool canHit = true;
    int kind;
    int lp;
    
public:
    Player(Vector2 position, float radius, int hp, float speed, float lowspeed, float minY, float maxX, float hitlessTime, int kind);
    ~Player();
    Prot *prot;
    float Lastt;
    void Update(float nowTime);
    void Move(float deltatime);
    void Draw();
    void Hit(float nowTime);
    bool useskill(float nowTime);
    int getHP();
    void Check(float nowTime); //判断盾是否消失
    Vector2 getPosition();
    float getRadius();
    bool getcanHit();
    void setPosition(Vector2 newPosition);
};
#endif
