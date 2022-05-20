#include "player.h"
#include "raylib.h"

#define MAXLP 5 //最大技能释放次数
#define PROT_LIMITTIME 5

PlayerHPBar::PlayerHPBar(float x, float y, float radius, float delta)
    : x(x), y(y), radius(radius), delta(delta)
{
}

void PlayerHPBar::Draw(int hp)
{
    for (int i = 0; i < hp; i++)
        DrawCircleV({x + delta * i, y}, radius, MAROON);
}

Player::Player(Vector2 position, float radius, int hp, float speed, float minY, float hitlessTime, int kind)
    : position(position), radius(radius), hp(hp), speed(speed), minY(minY), hitlessTime(hitlessTime), kind(kind),lp(MAXLP),prot(nullptr)
{
}

Player::~Player() {
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

void Player::Move()
{
    if (IsKeyDown(KEY_UP))
        position.y -= speed;
    if (IsKeyDown(KEY_DOWN))
        position.y += speed;
    if (IsKeyDown(KEY_LEFT))
        position.x -= speed;
    if (IsKeyDown(KEY_RIGHT))
        position.x += speed;
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
    DrawCircleV(position, radius, MAROON);
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

void Player::Check(float nowTime) {
    if (prot != nullptr && prot->Check(nowTime)) {
        delete prot;
        prot = nullptr;
    }
}

void Player::useskill(float nowTime) {
    if (kind == 0) {
        if(prot == nullptr && lp > 0)
            lp--,prot = new Prot(nowTime);
    }
}

bool Player::getcanHit() {
    return canHit;
}

void Player::setPosition(Vector2 newPosition) {
    position = newPosition;
}

Prot::Prot(float _StartTime):StartTime(_StartTime),LimitTime(PROT_LIMITTIME) {
}

void Prot::Draw(Vector2 p, float r) {
    Rectangle tmp = {p.x - r - 10, p.y - r - 10, 40, 5};
    DrawRectangleRec(tmp, GREEN);
}

void Prot::Hit() {

}

bool Prot::Check(float nowTime) {
    return nowTime - StartTime >= LimitTime;
}

