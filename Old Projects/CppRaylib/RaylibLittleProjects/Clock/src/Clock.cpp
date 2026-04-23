#include "Clock.hpp"



void Clock::draw()
{
    drawClock();
    drawHourArrow();
    drawMinArrow();
    drawHourMarks();
    drawSecArrow();
    DrawCircle(center.x, center.y, 30, BLACK);

}

void Clock::update()
{
    std::time_t currentTime = std::time(0);
    std::tm* localTime = std::localtime(&currentTime);
    second = localTime -> tm_sec; 
    minute = localTime -> tm_min;
    hour =   localTime -> tm_hour % 12;
}

void Clock::drawClock()
{
    int radius = GetScreenWidth()/2;
    DrawCircle(center.x, center.y, radius-50, LIGHTGRAY);
    DrawCircle(center.x, center.y, radius-60, WHITE);
    DrawRing(center, radius - 50, radius - 20, 0, 360, 1, BLACK);
}    

void Clock::drawHourMarks()
{
    Rectangle rec {400, 400, 16, 50};
    Vector2 hourMarkPosition = {8, 350};

    for(int i = 0; i < 12; i++){

        DrawRectanglePro(rec, hourMarkPosition, 30 * i, BLACK);
    }
}

void Clock::drawMinArrow()
{
    Rectangle minuteArrow {400, 400, 8, 320};
    Vector2 position {4, 320};

    DrawRectanglePro(minuteArrow, position, minute * 6.0, DARKGRAY);
}

void Clock::drawSecArrow()
{
    Rectangle minuteArrow {400, 400, 6, 400};
    Vector2 position {3, 340};

    DrawRectanglePro(minuteArrow, position, second * 6.0, RED);
}

void Clock::drawHourArrow()
{
    Rectangle hourArrow {400, 400, 18, 300};
    Vector2 position {9, 300};

    DrawRectanglePro(hourArrow, position, hour * 30 + minute * 0.5, BLACK);
}
