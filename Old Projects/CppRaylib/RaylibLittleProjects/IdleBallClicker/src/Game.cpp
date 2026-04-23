#include "Game.hpp"

Game::Game(int width, int height, char *title) : button({610, 70, 175, 40}, "Add Ball")
{
    InitWindow(width, height, title);
    SetTargetFPS(60);
}

Game::~Game()
{
    CloseWindow();
}

void Game::run(){

    gameLoop();
}

void Game::gameLoop() {

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground({80, 80, 80, 200});
        
        update();
        draw();

        EndDrawing();
    }
}

void Game::update() {
    if(button.clicked(GetMousePosition())){
        balls.push_back(Ball());
    }
    ballCount = balls.size()+1;
}
void Game::draw() {
    
    Rectangle rightArea {600, 60, 195, 790};
    Rectangle leftPanel {5, 60, 595, 790};
    DrawRectangleRounded(rightArea, 0.1f, 5, {40, 40, 40, 255});
    DrawRectangleRounded(leftPanel, 0.05f, 5, {120, 120, 120, 255});
    button.draw();
    for(auto& b : balls){
        b.draw();
    }
    drawScore();
}

