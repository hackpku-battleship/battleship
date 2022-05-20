#include "raylib.h"

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

class Player
{
    Vector2 position;
    float radius;
    int hp;
    const float speed;
    const float minY;
    const float hitlessTime;
    float lastHitTime = -1e300;
    bool canHit = true;
    int kind;
    int lp;
    Prot *prot;
public:
    Player(Vector2 position, float radius, int hp, float speed, float minY, float hitlessTime, int kind);
    ~Player();
    void Update(float nowTime);
    void Move();
    void Draw();
    void Hit(float nowTime);
    void useskill(float nowTime);
    int getHP();
    void Check(float nowTime); //判断盾是否消失
    Vector2 getPosition();
    float getRadius();
};

