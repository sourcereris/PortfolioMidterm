#pragma once

enum GameState {
	Menu,
	Playing,
	Lose,
	Reset,
	Pause,
	Settings,
	Shop
};

extern GameState g_currentGameState;