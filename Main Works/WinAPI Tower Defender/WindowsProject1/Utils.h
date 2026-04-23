#pragma once

#include "Globals.h"

void Transform(double*, double*);
void InverseTransform(double*, double*);
// Draw an image centered on position `p`
void DrawImage(HDC hdc, Image* image, KVector2 p);
void DrawImage(HDC hdc, Image* image, KVector2 p, double degree);
void DrawLine(HDC hdc, double x1, double y1, double x2, double y2, COLORREF c = RGB(0, 0, 0), int penStyle = PS_SOLID, int lineWidth = 1);
void DrawVector(HDC hdc, KVector2 p1, KVector2 p2, COLORREF c, int penStyle = PS_SOLID, int lineWidth = 1);
void DrawVector(HDC hdc, KComplex c1, KComplex c2, COLORREF c, int penStyle = PS_SOLID, int lineWidth = 1);

