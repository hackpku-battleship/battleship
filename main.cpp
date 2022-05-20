#include "raylib.h"
#include "init.h"
#include <cstring>

//class basicBullet a;

int main(void){
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    SetTargetFPS(60);
    Init::loop(screenWidth, screenHeight);
    CloseWindow();
    return 0;
}
