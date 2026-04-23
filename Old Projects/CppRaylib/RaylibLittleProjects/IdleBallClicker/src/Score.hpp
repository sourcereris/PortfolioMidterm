#pragma once
#include <raylib.h>
#include <sstream>
#include <iomanip> 
#include <string>

extern int score;

void drawScore();
void updateScore(int addToScore);