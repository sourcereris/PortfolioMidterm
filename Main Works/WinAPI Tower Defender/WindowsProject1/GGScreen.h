#pragma once

#include "Utils.h"

class GGScreen
{
	KVector2 _tPos; //triangle
	double _tSize = 16;
	KVector2 _buttonSize{150, 35};
	void ButtonShift(int, const wchar_t*);
	void DrawTriangle();
	void KeyStates();
	void DrawGameOver();
	void DrawScore();
public:
	GGScreen();
	~GGScreen();
	void Draw();
	void Update();
	int trigYshift = -1; // for triangle position next to a button
};

