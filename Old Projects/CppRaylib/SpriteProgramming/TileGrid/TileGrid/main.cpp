#include <PerlinNoise.hpp>
#include <random>
#include <iostream>
#include "Game.hpp"


int main() {
	
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dist(0, 987);

	int x = 55 / 60;
	std::cout << x;

	Game game;

	return 0;
}