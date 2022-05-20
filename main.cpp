#include "raylib.h"
#include <bits/stdc++.h>
#include "basicBullet.h"
#include "fishBullet.h"
#include "bulletManager.h"
#include "player.h"
#include "enemy.h"
#include "init.h"
#include <cstring>

int main(void)
{
    freopen("log", "w", stderr);
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    SetTargetFPS(60);
    Init::loop(screenWidth, screenHeight);
    CloseWindow();
    return 0;
}
