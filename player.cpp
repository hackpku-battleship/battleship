#include "player.h"
#include "bullet.h"
#include "bulletManager.h"
#include "raylib.h"
#include "enemymanager.h"

PlayerBar::PlayerBar(float x, float y, float radius, float delta, Color col)
    : x(x), y(y), radius(radius), delta(delta), col(col)
{
}

void PlayerBar::Draw(int hp)
{
    for (int i = 0; i < hp; i++)
        DrawCircleV({x + delta * i, y}, radius, col);
}

Player::Player(Vector2 position, float radius, int hp, float speed, float lowspeed, float minY, float maxX, float hitlessTime, int kind)
    : position(position), radius(radius), hp(hp), speed(speed), lowspeed(lowspeed), minY(minY), maxX(maxX), hitlessTime(hitlessTime), kind(kind), lp(MAXLP), prot(nullptr), Lastt(-2.0)
{
    if (kind == 0)
        texture = LoadTexture("source/yuka.png");
    else if (kind == 1)
        texture = LoadTexture("source/reimu.png");
    else
        texture = LoadTexture("source/marisa.png");
}

Player::~Player()
{
    if (prot != nullptr)
        delete prot;
    UnloadTexture(texture);
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
    if (position.x > maxX)
        position.x = maxX;
}

void Player::Draw()
{
    if (prot != nullptr)
        prot->Draw(position, radius);
    const float playerradius = 40;
    int frameWidth = texture.width;
    int frameHeight = texture.height;
    Rectangle sourceRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};
    Rectangle destRec = {position.x, position.y, playerradius * 2.0f, playerradius * 2.0f};
    Vector2 origin = {playerradius, playerradius};
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0, WHITE);
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        DrawCircleV(position, radius, WHITE);
        DrawRing(position, radius, radius + 2, 0.f, 360.f, 1, BLACK);
    }
}

int Player::getHP()
{
    return hp;
}

int Player::getLP()
{
    return lp;
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
        if (lp == 0 || nowTime - Lastt < BALLCD)
            return 0;
        lp--, Lastt = nowTime;
        return 1;
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
    tex = LoadTexture("source/kasa_mid.png");
}

void Prot::Draw(Vector2 p, float r)
{
    Rectangle area = PROT_REC;
    DrawTextureTiled(tex, {0, 0, tex.width, tex.height}, area, {0, 0}, 0, 1, WHITE);
}

void Prot::Hit()
{
}

bool Prot::Check(float nowTime)
{
    return nowTime - StartTime >= LimitTime;
}

Atk::Atk(float _R) : R(_R), Speed(FOOTBALLSP), attack(BALLATTACK)
{
}

void Atk::Draw()
{
    static Texture2D tex = LoadTexture("source/dog.png");
    for (auto i : Ps)
        DrawTexture(tex, i.x-50, i.y-50, WHITE);
}

void Atk::HitBullet(BulletManager *enemyBullets)
{
    auto bullets = enemyBullets->getBullets();
    for (auto j : Ps)
        for (int i = 0; i < bullets.size(); i++)
            if (bullets[i]->checkBox(j, R))
            {
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                --i;
            }
    enemyBullets->setBullets(bullets);
}

void Atk::HitEnemy(EnemyManager *enemys)
{
    // todo : ????????????, ????????????, (????????????)
    for (auto i = Ps.begin(); i != Ps.end();){
        bool flag = false;
        for (auto j : enemys->enemys)
            if (CheckCollisionCircles(*i, R, j->pos, j->r))
            {
                i=Ps.erase(i);
                flag = true;
                j->hp -= attack;
                break;
            }
        if(!flag) i++;
    }
}

void Atk::Check(int screenWidth, int screenHeight)
{ //??????????????????
    for (auto i = Ps.begin(); i != Ps.end();)
    {
        auto j = *i;
        if (j.x < -R || j.y < -R || j.x > screenWidth + R || j.y > screenHeight + R)
            i = Ps.erase(i);
        else
            i++;
    }
}

void Atk::Move(float deltatime)
{
    for (auto i = Ps.begin(); i != Ps.end(); i++)
        (*i).y -= Speed * deltatime;
}

void Atk::Add(Vector2 pos)
{
    pos.y -= R;
    Ps.push_back(pos);
}
