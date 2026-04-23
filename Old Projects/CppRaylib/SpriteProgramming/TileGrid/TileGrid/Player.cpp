#include "Player.hpp" 
#include <iostream>

Vector2 position = { 0 };
const int SPRITE_SIZE_IN_PIXELS = 192;
int spriteAnimationRow = 0; //which row will rect cut from png file in DrawPlayer()

Player::Player(){
	IdlePlayerTexture = { 0 };
	WalkPlayerTexture = { 0 };
	RunPlayerTexture  = { 0 };
}
Player::~Player() {
	UnloadTexture(IdlePlayerTexture);
	UnloadTexture(WalkPlayerTexture);
	UnloadTexture(SRunPlayerTexture);
	UnloadTexture(RunPlayerTexture);
	UnloadTexture(def);
}
void Player::UpdateAndDraw()
{
	UpdateInputs();
	DrawPlayer();
}
void Player::InitPlayer()
{
	LoadPlayerTextures();
}
void Player::UpdateInputs()
{
	static int speed = 3;
	float diagonalSpeed = sqrt(0.5) * speed;

	if(IsKeyPressed(KEY_I)) speed += 5;
	int buttonsPressed = 0;
	if (IsKeyDown(KEY_A)) ++buttonsPressed;
	if (IsKeyDown(KEY_D)) ++buttonsPressed;
	if (IsKeyDown(KEY_W)) ++buttonsPressed;
	if (IsKeyDown(KEY_S)) ++buttonsPressed;

	//if()

	if (buttonsPressed > 2 || buttonsPressed == 0) {
		def = SIdlePlayerTexture;
		state = Idle;
		return;
	}
	def = RunPlayerTexture;
	state = Run;
	if (buttonsPressed == 1) {
		if (IsKeyDown(KEY_A)) {
			position.x -= speed;
			spriteAnimationRow = 1;
		}
		if (IsKeyDown(KEY_D)) {
			position.x += speed;
			spriteAnimationRow = 2;
		}
		if (IsKeyDown(KEY_W)) {
			position.y -= speed;
			spriteAnimationRow = 3;
		}
		if (IsKeyDown(KEY_S)) {
			position.y += speed;
			spriteAnimationRow = 0;
		}
	}
	else {
		if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W)) {
			position.x -= diagonalSpeed;
			position.y -= diagonalSpeed;
			spriteAnimationRow = 1;
		}
		if (IsKeyDown(KEY_A) && IsKeyDown(KEY_S)) {
			position.x -= diagonalSpeed;
			position.y += diagonalSpeed;
			spriteAnimationRow = 1;
		}
		if (IsKeyDown(KEY_D) && IsKeyDown(KEY_S)) {
			position.x += diagonalSpeed;
			position.y += diagonalSpeed;
			spriteAnimationRow = 2;
		}
		if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W)) {
			position.x += diagonalSpeed;
			position.y -= diagonalSpeed;
			spriteAnimationRow = 2;
		}
	}
}

void Player::DrawPlayer()
{
	static float index = 0;
	static float i = 0;
	Vector2 spritePos{ GetScreenWidth() / 2 - 128, GetScreenHeight() / 2 - 128 };
	int row = SPRITE_SIZE_IN_PIXELS * spriteAnimationRow;

	Rectangle r{ SPRITE_SIZE_IN_PIXELS * index, row, SPRITE_SIZE_IN_PIXELS, SPRITE_SIZE_IN_PIXELS};

	DrawTextureRec(def, r, spritePos, WHITE);

	if (index >= 8) {
		index = 0;
		i = 0;
	}
	i += 6.f/GetFPS();
	index = round(i);
}

void Player::LoadPlayerTextures()
{	
	Image img = LoadImage("Images/Idle.png");
	ImageResizeNN(&img, img.width * 3, img.height * 3);
	IdlePlayerTexture = LoadTextureFromImage(img);
	
	
	img = LoadImage("Images/Walk.png");
	ImageResizeNN(&img, img.width * 3, img.height * 3);
	WalkPlayerTexture = LoadTextureFromImage(img);

	img = LoadImage("Images/Run.png");
	ImageResizeNN(&img, img.width * 3, img.height * 3);
	RunPlayerTexture = LoadTextureFromImage(img);

	img = LoadImage("Images/SRun.png");
	ImageResizeNN(&img, img.width * 3, img.height * 3);
	SRunPlayerTexture = LoadTextureFromImage(img);

	img = LoadImage("Images/SIdle.png");
	ImageResizeNN(&img, img.width * 3, img.height * 3);
	SIdlePlayerTexture = LoadTextureFromImage(img);
	def = LoadTextureFromImage(img);


	UnloadImage(img);
}
