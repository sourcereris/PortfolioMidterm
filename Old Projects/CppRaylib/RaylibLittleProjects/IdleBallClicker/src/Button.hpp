#pragma once
#include <raylib.h>
#include <string>
#include <math.h>
#include "Score.hpp"

extern int ballCount;
extern int score;

class Button{
    public:
        Button(Rectangle rec, std::string text);
        void draw();
        bool clicked(Vector2 position);
    private:
        Rectangle buttonPossition;
        bool wasButtonPressed;
        bool mouseOnButton(Vector2 mousePossition);
        std::string text;
        int scoreToUpgrade = 0;
};