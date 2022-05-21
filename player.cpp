#include "player.h"
#include "bullet.h"
#include "bulletManager.h"
#include "raylib.h"

PlayerHPBar::PlayerHPBar(float x, float y, float radius, float delta)
    : x(x), y(y), radius(radius), delta(delta)
{
}

void PlayerHPBar::Draw(int hp)
{
    for (int i = 0; i < hp; i++)
        DrawCircleV({x + delta * i, y}, radius, MAROON);
}

Player::Player(Vector2 position, float radius, int hp, float speed, float lowspeed, float minY, float hitlessTime, int kind, char *filename)
    : position(position), radius(radius), hp(hp), speed(speed), lowspeed(lowspeed), minY(minY), hitlessTime(hitlessTime), kind(kind), lp(MAXLP), prot(nullptr), Lastt(-2.0)
{
    texture = LoadTexture(filename);
}

Player::~Player()
{
    if (prot != nullptr)
        delete prot;
}

void Player::Hit(float nowTime)
{
    if (canHit)
    {
        hp -= 1;
        canHit = false;
        lastHitTime = nowTime;
    }
}

void Player::Update(float nowTime)
{
    if (nowTime - lastHitTime > hitlessTime)
        canHit = true;
}

void Player::Move(float deltatime)
{
    float currentSpeed = speed;
    if (IsKeyDown(KEY_LEFT_SHIFT))
        currentSpeed = lowspeed;
    if (IsKeyDown(KEY_UP))
        position.y -= currentSpeed * deltatime;
    if (IsKeyDown(KEY_DOWN))
        position.y += currentSpeed * deltatime;
    if (IsKeyDown(KEY_LEFT))
        position.x -= currentSpeed * deltatime;
    if (IsKeyDown(KEY_RIGHT))
        position.x += currentSpeed * deltatime;
    if (position.y < minY)
        position.y = minY;
    if (position.y > GetScreenHeight())
        position.y = GetScreenHeight();
    if (position.x < 0)
        position.x = 0;
    if (position.x > GetScreenWidth())
        position.x = GetScreenWidth();
}

void Player::Draw()
{
    if (prot != nullptr)
        prot->Draw(position, radius);
    int frameWidth = texture.width;
    int frameHeight = texture.height;
    Rectangle sourceRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};
    Rectangle destRec = {position.x, position.y, radius * 2.0f, radius * 2.0f};
    Vector2 origin = {radius, radius};
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0, WHITE);
    // DrawCircleV(position, radius, MAROON);
}

int Player::getHP()
{
    return hp;
}

Vector2 Player::getPosition()
{
    return position;
}

float Player::getRadius()
{
    return radius;
}

void Player::Check(float nowTime)
{
    if (prot != nullptr && prot->Check(nowTime))
    {
        delete prot;
        prot = nullptr;
    }
}

bool Player::useskill(float nowTime)
{
    if (kind == 0)
    {
        if (prot == nullptr && lp > 0)
        {
            lp--, prot = new Prot(nowTime);
            return 1;
        }
        return 0;
    }
    else if (kind == 1)
    {
        if (lp == 0)
            return 0;
        if (nowTime - Lastt > LASTOFRING)
        {
            Lastt = nowTime, lp--;
        }
        return 1;
    }
    else
    {
    }
}

bool Player::getcanHit()
{
    return canHit;
}

void Player::setPosition(Vector2 newPosition)
{
    position = newPosition;
}

Prot::Prot(float _StartTime) : StartTime(_StartTime), LimitTime(PROT_LIMITTIME)
{
}

void Prot::Draw(Vector2 p, float r)
{
    // Rectangle tmp = {p.x - r - 10, p.y - r - 10, 40, 5};
    DrawRectangleRec(PROT_REC, GREEN);
}

void Prot::Hit()
{
}

bool Prot::Check(float nowTime)
{
    return nowTime - StartTime >= LimitTime;
}
