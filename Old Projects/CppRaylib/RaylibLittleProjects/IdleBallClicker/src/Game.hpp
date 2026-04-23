#pragma once
#include <raylib.h>
#include <vector>
#include "Ball.hpp"
#include "Score.hpp"
#include "Button.hpp"

extern int ballCount;

class Game{
    public:
        Game(int width, int height, char* title);
        ~Game();
        void run();
    private:
        void gameLoop();
        void update();
        void draw();
        Button button;
        std::vector<Ball> balls;
};