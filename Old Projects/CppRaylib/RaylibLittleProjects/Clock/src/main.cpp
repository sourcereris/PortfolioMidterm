#include <raylib.h>
#include "Game.hpp"

int main() 
{
    int screenWidth = 800;
    int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose()){

        BeginDrawing();
            ClearBackground({201, 240, 255, 255});
            game.update();
            game.draw();
        EndDrawing();
    }
    
    CloseWindow();
}