#include "raylib.h"

class PlayerHPBar
{
    float x, y, radius, delta;

public:
    PlayerHPBar(float x, float y, float radius, float delta);
    void Draw(int hp);
};

class Player
{
    Vector2 position;
    float radius;
    int hp;
    const float speed;
    const float minY;
    const float hitlessTime;
    const float lowspeed;
    float lastHitTime = -1e300;
    bool canHit = true;

public:
    Player(Vector2 position, float radius, int hp, float speed, float lowspeed, float minY, float hitlessTime);
    void Update(float nowTime);
    void Move(float deltatime);
    void Draw();
    void Hit(float nowTime);
    int getHP();
    Vector2 getPosition();
    float getRadius();
    bool getcanHit();
    void setPosition(Vector2 newPosition);
};
