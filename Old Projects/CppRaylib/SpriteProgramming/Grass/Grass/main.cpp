#include <raylib.h>
#include <random>
#include <thread>
#include <string>
#include <iostream>
#include <PerlinNoise.hpp>

std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<int> dist(1, 80);
std::uniform_real_distribution<double> ddist(-1, 1);

float Lerp(float, float, float);
void shufle(Image&);
void drawLilJimmy(Texture2D&, Texture2D&, Image&);

Color green = { 105, 140, 59, 255 };
Color darkGreen = { 79,  97, 56, 255 };
Color brown = { 95,73,50, 255 };
Color darkBrown = { 77,62,49, 255 };
siv::PerlinNoise noise;

Rectangle lilrec = { 0 };

int main() {

	char* siz;;
	char size;
	std::cout << sizeof(siz) << "size\n";

	InitWindow(1200, 800, "gg");
	SetTargetFPS(30);

	RenderTexture canvas = LoadRenderTexture(600, 600);
	Image img = LoadImageFromTexture(canvas.texture);
	UnloadRenderTexture(canvas);
	
	RenderTexture c = LoadRenderTexture(360, 360);
	Image ig = LoadImageFromTexture(c.texture);
	UnloadRenderTexture(c);

	shufle(img);
	Texture2D texture = LoadTextureFromImage(img);
	Image i = LoadImageFromTexture(texture);
	Texture2D t = LoadTextureFromImage(ig);
	UnloadImage(ig);


	while (!WindowShouldClose()) {
		
		BeginDrawing();
		ClearBackground(WHITE);

		if (IsKeyPressed(KEY_SPACE)) {
			shufle(img);
			UpdateTexture(texture, img.data);
		}

		if (IsKeyPressed(KEY_P)) {
			ExportImage(img, "Grass.png");
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 pos = GetMousePosition();
			lilrec = {pos.x, pos.y, 12, 12};	
		}
		drawLilJimmy(texture, t, i);

		DrawTexture(texture, 0, 0, WHITE);

		EndDrawing();
	}

	UnloadTexture(t);
	UnloadImage(i);
	UnloadImage(img);
	UnloadTexture(texture);
	return 0;
}

void shufle(Image& img) {
	double noiseValue = 0;
	float t;
	

	for (int i = 0; i < img.width; ++i) {
		for (int j = 0; j < img.width; ++j) {

			
			

			if (i < 150) {
				noiseValue = noise.noise2D(i+ ddist(gen), j+ ddist(gen)) + 0.5f;
				t = (float)i / 150;

				float DarkGreen = Lerp(.2f, .5f, t);

				if(noiseValue < DarkGreen) ImageDrawPixel(&img, i, j, darkGreen);
				else ImageDrawPixel(&img, i, j, green);

			}else if (i < 300) {
				noiseValue = noise.noise2D(i + ddist(gen), j + ddist(gen)) + 0.5f;
				t = ((float)i - 150) / 150;

				float Green = Lerp(.5f, .2f, t);
				float Brown = Lerp(.2f, .4f, t);
				float Darkbrown = Lerp(-1.f, .05f, t);

				if (noiseValue < Darkbrown) ImageDrawPixel(&img, i, j, darkBrown);
				else if (noiseValue < Green) ImageDrawPixel(&img, i, j, green);
				else if (noiseValue < Brown) ImageDrawPixel(&img, i, j, brown);
				else ImageDrawPixel(&img, i, j, darkGreen);
			}
			else if (i < 450) {
				noiseValue = noise.noise2D(i + ddist(gen), j + ddist(gen)) + 0.5f;
				if (noiseValue < 0) noiseValue = 0;
				t = ((float)i - 300) / 150;

				float DarkGreen = Lerp(.7f, .01f, t);
				float Brown = Lerp(.99f, .7f, t);
				float Green = Lerp(.2f, .1f, t);

				if (noiseValue < Green) ImageDrawPixel(&img, i, j, green);
				else if (noiseValue < DarkGreen) ImageDrawPixel(&img, i, j, darkGreen);
				else if (noiseValue < Brown) ImageDrawPixel(&img, i, j, brown);
				else ImageDrawPixel(&img, i, j, darkBrown);
			}
			else {
				noiseValue = noise.noise2D(i + ddist(gen), j + ddist(gen)) + 0.5f;
				t = ((float)i - 450) / 150;

				float Brown = Lerp(.7f, .2f, t);
				float Green = Lerp(.01f, .0f, t);

				if (noiseValue < Green) ImageDrawPixel(&img, i, j, green);
				else if (noiseValue < Brown) ImageDrawPixel(&img, i, j, brown);
				else ImageDrawPixel(&img, i, j, darkBrown);
			}

			//Color{ 105, 140, 59, 255 }	green
			//Color{ 88, 112, 56, 255 }		dark green
			//Color{ 95,73,50, 255 }		brown
			//Color{ 77,62,49, 255 }		dark brown
			
		}
	}
}

float Lerp(float a, float b,  float t) {
	return (a + (b - a) * t);
}

void drawLilJimmy(Texture2D& txt, Texture2D& t, Image& i){
	UnloadImage(i);
	i = LoadImageFromTexture(txt);
	ImageCrop(&i, lilrec);
	ImageResizeNN(&i, 360, 360);
	UpdateTexture(t, i.data);
	DrawTexture(t, 840, 440, WHITE);
}