#include "MenuScreen.h"

MenuScreen::MenuScreen(){}
MenuScreen::~MenuScreen(){}

void MenuScreen::Update()
{
    KeyStates();
}

void MenuScreen::Draw()
{
    ButtonShift(-1, L"Start");
    ButtonShift(0, L"Settings");
    ButtonShift(1, L"Exit");
    DrawTriangle();
}

void MenuScreen::ButtonShift(int shift, const wchar_t* text)
{
    double buttonY = g_center.y - _buttonSize.y / 2;
    double buttonX = g_center.x - _buttonSize.x / 2;
    int buttonShift = _buttonSize.y * shift + 5 * shift;

    KVector2 buttonPosition{ buttonX, buttonY + buttonShift };
    Rect rect(buttonPosition.x, buttonPosition.y, _buttonSize.x, _buttonSize.y); // x, y, width, height
    PointF pointF(g_center.x - _buttonSize.x / 2, buttonPosition.y);

    Graphics graphics(g_hdc);

    Pen         pen(Color(255, 0, 0, 0), 2); // Black pen, 2px thickness
    SolidBrush  brush1(Color(255, 0, 0, 0));
    FontFamily  fontFamily(L"Agency FB");
    Font        font(&fontFamily, 24, FontStyleBold, UnitPixel);

    graphics.DrawRectangle(&pen, rect);
    graphics.DrawString(text, -1, &font, pointF, &brush1);
    DrawTitle();
}
void MenuScreen::DrawTitle()
{
    Graphics graphics(g_hdc);
    FontFamily  fontFamily(L"Agency FB");
    SolidBrush  brush1(Color(255, 0, 0, 0));
    Font        font1(&fontFamily, 96, FontStyleBold, UnitPixel);

    RectF boundingBox;
    RectF layoutRect(0, 0, 1000, 1000);
    graphics.MeasureString(L"KNIGHTFALL", -1, &font1, layoutRect, &boundingBox);

    PointF pos(g_center.x - boundingBox.Width / 2.0f, 50.0f); // Use PointF constructor with float values  
    graphics.DrawString(L"KNIGHTFALL", -1, &font1, pos, &brush1);
}

void MenuScreen::DrawTriangle()
{
    double trigX = -(_tSize / 3.232); //3.232 for center of triangle
    double trigY = _tSize / 2;

    double buttonYshift = _buttonSize.y * trigYshift + 5 * trigYshift;
    _tPos = { g_center.x - (_buttonSize.x / 2 + 1.5 * _tSize), (g_center.y - trigY) + buttonYshift };

    double angle = .0;
    Graphics   graphics(g_hdc);

    graphics.ResetTransform();
    graphics.TranslateTransform(_tPos.x - trigX, _tPos.y + trigY); 
    graphics.RotateTransform(angle);

    SolidBrush brush(Color(255, 0, 0, 0));

    PointF triangle[3] = {
        PointF(trigX, -(trigY)),   // Top
        PointF(_tSize + trigX, 0.0f),     // Right
        PointF(trigX, trigY)     // Bottom
    };
    graphics.FillPolygon(&brush, triangle, 3);

}

void MenuScreen::KeyStates()
{
    static bool isUpButtonPressed = false;
    static bool isDownButtonPressed = false;

    bool isUpPressed = (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000);
    if (!isUpPressed)
    {
        isUpButtonPressed = false;
    }
    else if (!isUpButtonPressed)
    {
        --trigYshift;
        isUpButtonPressed = true;
    }

    bool isDownPressed = (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000);
    if (!isDownPressed)
    {
        isDownButtonPressed = false;
    }
    else if (!isDownButtonPressed)
    {
        ++trigYshift;
        isDownButtonPressed = true;
    }

    if (trigYshift > 1) trigYshift = -1;
    else if (trigYshift < -1) trigYshift = 1;

    bool isEnterPressed = (GetAsyncKeyState(VK_RETURN) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8000);
    static bool EnterChanged = false;
    static bool Enter = false;
    if (EnterChanged != isEnterPressed) {
        EnterChanged = isEnterPressed;
        if (!EnterChanged) Enter = true;
    }

    if (Enter) {
        if (trigYshift == 1)
        {
            DestroyWindow(g_hwnd);
        }
        if (trigYshift == -1) {
            g_currentGameState = Reset;
        }
    }
    Enter = false;
}
