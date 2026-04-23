#include "Game.hpp"

Vector2 windowSize{1280, 720};

Game::Game() 
{
	Init();
	GameLoop();
}

Game::~Game() 
{
	CloseWindow();
	UnloadAllTexture();
}

void Game::InitializeWindow() //Window Initialization always first!!!!!!!!!!!!!!
{
	InitWindow(windowSize.x, windowSize.y, "Game");
	SetTargetFPS(60);
}

void Game::Init()
{
	InitializeWindow();		//Window Initialization always first!!!!!!!!!!!!!!

	InitGrassTextures();
	mainPlayer.InitPlayer();
	world.InitRectangles();
}

void Game::GameLoop()
{
	while (!WindowShouldClose()) {
		
		if (IsKeyPressed(KEY_F)) {
			ToggleFullscreen();
		}
		if (IsWindowFullscreen()) {
			windowSize = {1920, 1080};
		}
		else windowSize = { 1280, 720 };

		BeginDrawing();
		ClearBackground(BLACK);

		world.UpdateAndDraw();
		mainPlayer.UpdateAndDraw();

		EndDrawing();

	}
}

