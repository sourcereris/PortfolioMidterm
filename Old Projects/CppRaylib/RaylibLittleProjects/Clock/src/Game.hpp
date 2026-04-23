#pragma once
#include <raylib.h>
#include "Clock.hpp"

class Game{
    public:
        Game();
        ~Game();
        void update();
        void draw();
    private:
        Clock clock {Vector2 {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}};
};