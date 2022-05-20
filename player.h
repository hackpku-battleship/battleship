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

public:
    Player(Vector2 position, float radius, int hp, float speed, float minY);
    void Move();
    void Draw();
    int getHP();
    Vector2 getPosition();
    float getRadius();
};
