#include "raylib.h"
#include "bullet.h"

basicBullet a;

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    while (!WindowShouldClose()){

        BeginDrawing();

            ClearBackground(RAYWHITE);
            
 


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
