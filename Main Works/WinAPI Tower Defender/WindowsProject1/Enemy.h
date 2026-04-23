#pragma once

#include "Utils.h"
#include "iostream"

class Enemy
{
	KVector2 _position;
	KVector2 _velocity;
	KTileManager* g_eTileManager = nullptr;
	double degree;
	double radianToDegree = 180.0 / 3.141592;
	bool ChechCollision(std::vector<EnemyBehaviour>::iterator&);
public:
	Enemy();
	~Enemy();
	void SpawnEnemy();
	void DrawEnemies();
	void Update();
	void Initialize();
	void Finalize();
};

