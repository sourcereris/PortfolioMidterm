#pragma once
#include "TileTextures.hpp"
#include "Player.hpp"
#include "World.hpp"

extern Vector2 windowSize;

class Game{
	void InitializeWindow();
	void Init();
	void GameLoop();
	Player mainPlayer;
	World world;
	
public:
	Game();
	~Game();
};

