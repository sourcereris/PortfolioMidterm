#pragma once

#include <windows.h>     // Must come first
#include <windef.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <random>
#include "KVector2.h"
#include "KComplex.h"
#include "KSpriteAnimator.h"
#include "KTime.h"
#include "GameState.h"

using namespace Gdiplus;
#pragma comment(lib,"winmm.lib")
#pragma comment( lib, "gdiplus.lib" )

//------- Handles ------------
extern HDC g_hdc;
extern HWND g_hwnd;

//------- Entities ------------
struct Bullet 
{
	KVector2 position;
	KVector2 velocity;
};

struct SidekickBehaviour
{
	KVector2 position;
	KVector2 velocity;
	KVector2 bulletInitialPosition;
};

struct EnemyBehaviour
{
	KVector2 position;
	KVector2 velocity;
};

//------- Sprites -------------
extern Image* g_image;
extern Image* g_bulletImage;
extern Image* g_gunImage;
extern KSpriteAnimator g_enemyAnimator;
extern KSpriteAnimator g_heartAnimator;

//------- coordinates ---------
extern POINT g_center;
extern int g_pixelPerUnit;
extern KVector2 g_mousePos;
extern KVector2 g_screenSize;

//------- time ----------------
extern KTime   g_time;

//------- arrays --------------
extern std::vector<Bullet> bullets;
extern std::vector<SidekickBehaviour> SKbullets; //Sidekick
extern std::vector<EnemyBehaviour> enemies;

//------- score ---------------
extern int score;
extern int lives;