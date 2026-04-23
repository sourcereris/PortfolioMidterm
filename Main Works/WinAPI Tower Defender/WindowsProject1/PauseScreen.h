#pragma once

#include "Utils.h"

class PauseScreen
{
	KVector2 _tPos; //triangle
	double _tSize = 16;
	KVector2 _buttonSize{ 150, 35 };
	void ButtonShift(int, const wchar_t*);
	void DrawTriangle();
	void KeyStates();
	void DrawTitle();
public:
	PauseScreen();
	~PauseScreen();
	void Update();
	void Draw();
	int trigYshift = -1;
};

