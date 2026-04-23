#include "World.hpp"
#include <math.h>
const int RENDER_DISTANCE = 625; // (2n + 1)^2 squere
const float TILE_SIZE = 60; //tile_size change does not work, grass texture png too small.

World::World() {
	InitNoise();
	noiseLerpArray.resize(RENDER_DISTANCE);
	RenderableTiles.resize(RENDER_DISTANCE);
	tiles.resize(50);
}

void World::InitNoise()
{
	const siv::PerlinNoise::seed_type seed = 1;
	const siv::PerlinNoise perlin{ seed };
}

void World::UpdateAndDraw() {
	TilesBasedOnPlayerPosition();
	Draw();
}

void World::TilesBasedOnPlayerPosition(){ // makes rectangle of tiles size(w x h) -> (2n + 1)^2
	Vector2 pos = position;

	static int DistToEdge = (sqrt(RENDER_DISTANCE) - 1) / 2; //from center rectangle to edge
	float dx = 0;			//to calculate coordinates of
	float dy = 0;			//upper left corner of every tiles
	int x = (int)pos.x / TILE_SIZE;		//on which tile player would stand
	int y = (int)pos.y / TILE_SIZE;		//TILE_SIZE x TILE_SIZE pixel grind

	

	int j, i, index;
	i = j = index = 0;

	while(index != RENDER_DISTANCE) {
		
		if (i >= sqrt(RENDER_DISTANCE)) {
			++j; i = 0;
		}
		
		dx = TILE_SIZE * x - (TILE_SIZE * DistToEdge - TILE_SIZE * i);		//iterates x axis acording to players position
		dy = TILE_SIZE * y - (TILE_SIZE * DistToEdge - TILE_SIZE * j);		//iterates y axis 16x16 tiles

		RenderableTiles[index] = {dx, dy};
		//std::cout << dx << " " << dy << " |" << index << '\n';
		++i; ++index;
	}

	for (int id = 0; id < RENDER_DISTANCE; ++id) {
		int len = (GrassTextures.width / TILE_SIZE) - 1; //tile_size change does not work, grass texture png too small.
		noiseLerpArray[id] = Lerp(0.f, len,
			noise.octave2D_01(RenderableTiles[id].x * 0.001f,
							  RenderableTiles[id].y * 0.001f, 8));	// calculates noise for diff coordinates
																	// for smooth ground texture transition
	}
}

void World::Draw()
{
	
	int index = 0;

	while (index != RENDER_DISTANCE) {

		RenderableTiles[index].x += GetScreenWidth() / 2 - 30 - position.x; //shift all rendered tiles half its size
		RenderableTiles[index].y += GetScreenHeight() /2 - 30 - position.y; //from 0,0 to mid of the screen

		//tiles.at(noiseLerpArray[index]).y *= GetRandomInt();
		DrawTextureRec(GrassTextures, tiles.at(noiseLerpArray[index]), RenderableTiles[index], WHITE);

		++index;
	}
}

void World::InitRectangles() {
	Rectangle r = { 0 };

	int len = GrassTextures.width / TILE_SIZE;	//tile_size change does not work, grass texture png too small.

	for (int i = 0; i < len; ++i) {
		r = Rectangle{ (float)i * TILE_SIZE, 0.f, TILE_SIZE, TILE_SIZE };
		tiles[i] = r;
	}
}

int World::GetRandomInt() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dist(0, 49);
	return dist(gen);
}




/* DOCUMENTATION

first calculate each tiles x and y, store it in a Vector2 RenderableTiles;
then for each x and y get perlinNoise store that in noiseLerpArray
															v
	----------------------------------------------------------------------
	Lerp is for noise (0 - 1) to make value between 0 and 50 for Rec array
	----------------------------------------------------------------------
*/