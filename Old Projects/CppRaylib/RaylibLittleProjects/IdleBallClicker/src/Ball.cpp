#include "Ball.hpp"

Ball::Ball()
{
    getRandomPosition();
    xDir = getRandomNumber(5);
    yDir = getRandomNumber(5);
}

Ball::~Ball()
{
}

void Ball::draw()
{

    DrawCircleV(position, 10, WHITE);
    update();
}

void Ball::update()
{
    int x = position.x;
    int y = position.y;

    if(x + xDir < 15){
        x = 15 - (x + xDir);
        xDir *= -1; //getRandomNumber(5);
        updateScore(1);
    }else if(x + xDir > 585){
        x = x + xDir - 585;
        xDir *= -1; //getRandomNumber(-5);
        updateScore(1);
    }else position.x = x + xDir;

    if(y + yDir < 75) {
        y = 75 - (y + yDir);
        yDir *= -1; //getRandomNumber(5);
        updateScore(1);
    }else if(y + yDir > 785){
        y = y + yDir - 785;
        yDir *= -1; //getRandomNumber(-5);
        updateScore(1);
    }else position.y = y + yDir;
    
}

void Ball::getRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int min = 70, max = 500;
    std::uniform_int_distribution<int> dist(min, max);

    position.x = dist(gen);
    position.y = dist(gen);
}

float Ball::getRandomNumber(int a)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dist(BALL_MIN_SPEED, BALL_MAX_SPEED); 

    return dist(gen)*a;
}
