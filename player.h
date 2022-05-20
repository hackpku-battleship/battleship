#include "raylib.h"

class Player
{
    Vector2 position = {400, 600};
    int hp = 5;
    const float speed = 50;
    const float minY = 300;

public:
    Vector2 getPosition();
    void Move();
    void Draw();
};
