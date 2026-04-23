#include "Utils.h"

void Transform(double* x, double* y)
{
    *x = g_center.x + (*x) * g_pixelPerUnit;
    *y = g_center.y + -(*y) * g_pixelPerUnit;
}

void InverseTransform(double* x, double* y)
{
    *x = ((*x) - g_center.x) / g_pixelPerUnit;
    *y = -((*y) - g_center.y) / g_pixelPerUnit;
}

// Draw an image centered on position `p`
void DrawImage(HDC hdc, Image* image, KVector2 p)
{
    if (image != nullptr) {
        int imageWidth = image->GetWidth();
        int imageHeight = image->GetHeight();
        Graphics graphics(hdc);
        Transform(&p.x, &p.y);
        graphics.DrawImage(image, (int)p.x - imageWidth / 2, (int)p.y - imageHeight / 2);
    }
}

void DrawImage(HDC hdc, Image* image, KVector2 p, double degree)
{
    if (image != nullptr) {
        int imageWidth = image->GetWidth();
        int imageHeight = image->GetHeight();

        Transform(&p.x, &p.y); // transform to client coordinate

        Graphics graphics(hdc);
        graphics.SetSmoothingMode(SmoothingModeHighQuality);
        graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);

        // push transform to the stack
        graphics.TranslateTransform((REAL)p.x, (REAL)p.y);
        graphics.RotateTransform((REAL)degree);
        graphics.TranslateTransform((REAL)-imageWidth / 2, (REAL)-imageHeight / 2);

        graphics.DrawImage(image, 0, 0, imageWidth, imageHeight);

        // reset transform
        graphics.ResetTransform();
    }
}

void DrawLine(HDC hdc, double x1, double y1, double x2, double y2, COLORREF c, int penStyle, int lineWidth)
{
    HPEN hPen;
    HPEN hPrevPen;
    hPen = CreatePen(penStyle, lineWidth, c);
    hPrevPen = (HPEN)SelectObject(hdc, hPen);

    Transform(&x1, &y1);
    MoveToEx(hdc, (int)x1, (int)y1, NULL);
    Transform(&x2, &y2);
    LineTo(hdc, (int)x2, (int)y2);

    SelectObject(hdc, hPrevPen);
    DeleteObject(hPen);
}

void DrawVector(HDC hdc, KVector2 p1, KVector2 p2, COLORREF c, int penStyle, int lineWidth)
{
    DrawLine(hdc, p1.x, p1.y, p2.x, p2.y, c, penStyle, lineWidth);
}

void DrawVector(HDC hdc, KComplex c1, KComplex c2, COLORREF c, int penStyle, int lineWidth)
{
    DrawLine(hdc, c1.r, c1.i, c2.r, c2.i, c, penStyle, lineWidth);
}