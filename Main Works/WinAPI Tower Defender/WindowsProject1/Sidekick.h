#pragma once

#include "Utils.h"

class Sidekick
{
	KTileManager* _sidekickTileManager = nullptr;
	KSpriteAnimator _animator;
	Image* _bulletImage = nullptr;
	void MoveTo();
	void Shoot();
	void DrawBullets();
	void UpdateBullets();
	bool CollisionWithEnemy(std::vector<SidekickBehaviour>::iterator&);
public:
	Sidekick();
	~Sidekick();
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
};

