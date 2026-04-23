#pragma once
#include "TileTextures.hpp"
#include "Player.hpp"
#include <raymath.h>
#include <PerlinNoise.hpp>
#include <random>


class World
{
	void InitNoise();
	void TilesBasedOnPlayerPosition();
	void Draw();
	
	int GetRandomInt();

	siv::PerlinNoise noise;

	std::vector<int> noiseLerpArray;		//stores noise value acording tile position
	std::vector<Vector2> RenderableTiles;
	std::vector<Rectangle> tiles;

public:
	World();
	void UpdateAndDraw();
	void InitRectangles();
};