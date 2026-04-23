#include "raylib.h"
#include "Game.hpp"

int main() 
{
    char title[] = "Screem";
    Game game(800, 800, title);
    game.run();
    return 0;
}