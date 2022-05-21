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
    InitWindow(screenWidth, screenHeight, "Battleship Shooting");

    InitAudioDevice();
    Mus::openMusic = LoadMusicStream("source/th10_01.mp3");
    Mus::stageMusics[0] = LoadMusicStream("source/th12_02.mp3");
    Mus::stageMusics[1] = LoadMusicStream("source/th12_02.mp3");
    Mus::stageMusics[2] = LoadMusicStream("source/th06_09.mp3");
    Mus::stageMusics[3] = LoadMusicStream("source/th10_13.mp3");
    Mus::endMusic = LoadMusicStream("source/th10_18.mp3");
    Mus::killedMusic = LoadMusicStream("source/killed-short.mp3");

    Img::Init();

    PlayMusicStream(Mus::openMusic);

    SetTargetFPS(60);
    Init::loop(screenWidth, screenHeight);

    UnloadMusicStream(Mus::openMusic);
    for (int i = 0; i <= 3; i++) UnloadMusicStream(Mus::stageMusics[i]);
    UnloadMusicStream(Mus::endMusic);
    UnloadMusicStream(Mus::killedMusic);

    Img::Release();
    
    CloseAudioDevice(); 
    CloseWindow();
    return 0;
}
