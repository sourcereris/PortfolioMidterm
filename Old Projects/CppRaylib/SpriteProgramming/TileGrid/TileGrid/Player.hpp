#pragma once
#include <raylib.h>

extern Vector2 position;

enum State {
	Idle,
	Run,
	SRun,
	Walk
};

class Player
{
	void UpdateInputs();
	void DrawPlayer();
	void LoadPlayerTextures();
	
	Texture2D def;
	Texture2D IdlePlayerTexture;
	Texture2D WalkPlayerTexture;
	Texture2D RunPlayerTexture;
	Texture2D SRunPlayerTexture;
	Texture2D SIdlePlayerTexture;
	State state = Idle;
public:
	Player();
	~Player();
	void UpdateAndDraw();
	void InitPlayer();
};

