#include <raylib.h>
#include <math.h>
#include <iostream>
#include "Game.hpp"
#include "ClosestPoint.hpp"

int main() 
{
    const Color darkGreen = DARKGRAY;

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    
    Game game;

    // for(int i = 0; i < 6; i++){
    //     float xoffset = cos(60*i*DEG2RAD)*sqrt(3)*50;
    //     float yoffset = sin(60*i*DEG2RAD)*sqrt(3)*50;
    //     game.addHexagon({400.0f + xoffset, 400.0f + yoffset});
    // }

    // for(int i = 0; i < 12; i++){

    //     if(i % 2 != 0){
    //         float xoffset = cos(30*i*DEG2RAD)*3*50;
    //         float yoffset = sin(30*i*DEG2RAD)*3*50;
    //         game.addHexagon({400.0f + xoffset, 400.0f + yoffset});
    //     }else{
    //         float xoffset = cos(30*i*DEG2RAD)*2*sqrt(3)*50;
    //         float yoffset = sin(30*i*DEG2RAD)*2*sqrt(3)*50;
    //         game.addHexagon({400.0f + xoffset, 400.0f + yoffset});
    //     }
    // }

    // for(int i = 0; i < 18; i++){

    //         float xoffset = cos(PI/9*i)*sqrt(21.f)*50.f;
    //         float yoffset = sin(PI/9*i)*sqrt(21.f)*50.f;
    //     if(i % 3 != 0)

    //         game.addHexagon({400.0f + xoffset, 400.0f + yoffset});
    //     else{
    //         xoffset = cos(PI/9*i)*3*sqrt(3)*50;
    //         yoffset = sin(PI/9*i)*3*sqrt(3)*50;
    //         game.addHexagon({400.0f + xoffset, 400.0f + yoffset});
    //     }
    // }

    float size = 20;
    int rotate = 0;
    int range = 14;

    Vector2 v {sqrt(3)*60,    0};
    Vector2 w {sqrt(0.75)*60, 90};

    Vector2 ogv = v;
    Vector2 ogw = w;

    std::vector<Vector2> points;

    for(int i = -range; i < range; i++){
        for(int j = -range; j < range; j++){

            Vector2 center {i * v.x + j * w.x, i * v.y + j * w.y};
            if(center.x >= 0 && center.x < screenWidth && center.y >= 0 && center.y < screenHeight)
            points.push_back(Vector2{static_cast<float>(i), static_cast<float>(j)});
            //DrawPoly(center, 6, size, 90, WHITE);
        }
    }

    int count = 0;
    int c = count;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(darkGreen);
            count = game.getListSize();
            game.draw();

            for(int i = -range; i <= range; i++){
                for(int j = -range; j <= range; j++){

                    Vector2 center {v.x * j + w.x * i, v.y * j + w.y * i};
                    DrawPolyLines(center, 6, size, 90, WHITE);
                }
            }

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                game.addHexagon(GetClosestPoint(v, w, GetMousePosition()));
            }
            if(GetMouseWheelMove() > 0) size += 1;
            if(GetMouseWheelMove() < 0 && size > 0) size -= 1;
            if(IsKeyDown(KEY_S)) {
                v.x *= 0.9; v.y *= 0.9;
                w.x *= 0.9; w.y *= 0.9;
                size *= 0.9;
                std::cout << "pressed S\n"; 
            }
            if(IsKeyDown(KEY_W)) {
                v.x *= 1.1; v.y *= 1.1;
                w.x *= 1.1; w.y *= 1.1;
                size *= 1.1;
                std::cout << "pressed W\n"; 
            }

            if(c != count){
                printf("list size: %d", count);
                c = count;
            }
            // for(int i = 0; i < 10; i++){
            //     for(int j = 0; j < 10; j++){
                    
            //         DrawCircle(w.x*j, w.y*i, 3, WHITE);
            //     }
            // }

        EndDrawing();
    }
    
    for(Vector2 p : points){
        printf("X: %.2f and Y: %.2f\n", p.x, p.y);
    }
    
    CloseWindow();
}