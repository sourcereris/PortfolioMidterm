#include "Score.hpp"

void drawScore()
{
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2) << score;

    std::string text = ss.str();

    DrawText(text.c_str(), GetScreenWidth()/2 - text.length()*5, 20, 20, WHITE);
}

void updateScore(int addToScore){
    score += addToScore;
}