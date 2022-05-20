#include "raylib.h"
#include "bullet.h"
#include "init.h"

//class basicBullet a;

int main(void){
    const int screenWidth = 1600;
    const int screenHeight = 900;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    while (!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(RAYWHITE);
            
 


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
