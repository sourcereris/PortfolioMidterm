#include "TileTextures.hpp"
#include <iostream>
Texture GrassTextures = { 0 };

void InitGrassTextures() // scale 10x from 600x12 to 6000x120 pixels and loads
{
	GrassTextures = LoadTexture("Images/Grass.png");
	Image image = LoadImageFromTexture(GrassTextures);
	ImageResizeNN(&image, image.width * 5, image.height * 5);
	UnloadTexture(GrassTextures);
	GrassTextures = LoadTextureFromImage(image);

	UnloadImage(image);
}

void UnloadAllTexture()
{
	UnloadTexture(GrassTextures);
}

