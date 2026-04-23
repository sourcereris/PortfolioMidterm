#pragma once

#include "Utils.h"

class Gun
{
	KVector2 _position;
	KVector2 _velocity;
	double _degree;
	double _radianToDegree = 180.0 / 3.141592;
	KTileManager* _heartTileManager = nullptr;
	void DrawBullets();
	void DrawGun();
public:
	Gun();
	~Gun();
	void LoadMag(int, int); //This function is called on mouseLbutton press
	void Update();
	void Draw();
	void Initialize();
	void Finalize();
};

