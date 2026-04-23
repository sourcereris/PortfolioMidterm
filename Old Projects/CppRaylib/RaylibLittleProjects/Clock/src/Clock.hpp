#pragma once
#include <raylib.h>
#include <ctime>

//static const Vector2 centerPosition = {static_cast<float>(GetScreenWidth() / 2), 
//                                static_cast<float>(GetScreenHeight() / 2)};

class Clock{
    public:
        Clock(Vector2 center) : center(center), second(0){};
        void draw();
        void update();
    private:
        Vector2 center;
        void drawClock();
        void drawHourMarks();
        void drawMinArrow();
        void drawSecArrow();
        void drawHourArrow();
        int second, minute, hour;
};