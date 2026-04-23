#pragma once
#include <raylib.h>
#include <random>
#include "Score.hpp"

class Ball{
    public:
        Ball();
        ~Ball();
        void draw();
        
    private:
    void getRandomPosition();
    float getRandomNumber(int a);
    void update();
    Vector2 position;
    float xDir, yDir;
    int BALL_MIN_SPEED = 1;
    int BALL_MAX_SPEED = 1;
};