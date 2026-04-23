#include "GGScreen.h"
#include <sstream>

GGScreen::GGScreen() {}
GGScreen::~GGScreen() {}

// Main draw function for the "Game Over" screen
void GGScreen::Draw()
{
    // Draws each button with vertical shifts: Play Again, Shop, Menu
    ButtonShift(-1, L"Play Again");
    ButtonShift(0, L"Shop");
    ButtonShift(1, L"Menu");

    // Draw selector triangle over currently selected button
    DrawTriangle();
}

// Update logic to handle user input
void GGScreen::Update()
{
    KeyStates();
}

// Draws a UI button with a text label and draws game over screen elements
void GGScreen::ButtonShift(int shift, const wchar_t* text)
{
    // Calculate button position based on center and shift index
    double buttonY = g_center.y - _buttonSize.y / 2;
    double buttonX = g_center.x - _buttonSize.x / 2;
    int buttonShift = _buttonSize.y * shift + 5 * shift;

    KVector2 buttonPosition{ buttonX, buttonY + buttonShift };

    // Define button rectangle
    Rect rect(buttonPosition.x, buttonPosition.y, _buttonSize.x, _buttonSize.y);
    PointF pointF(g_center.x - _buttonSize.x / 2, buttonPosition.y);

    // Draw the button outline and text
    Graphics graphics(g_hdc);
    Pen pen(Color(255, 0, 0, 0), 2); // Black pen
    SolidBrush brush1(Color(255, 0, 0, 0)); // Black fill
    FontFamily fontFamily(L"Agency FB");
    Font font(&fontFamily, 24, FontStyleBold, UnitPixel);

    graphics.DrawRectangle(&pen, rect);
    graphics.DrawString(text, -1, &font, pointF, &brush1);

    // Draws static elements once per button (but harmless)
    DrawGameOver();
    DrawScore();
}

// Draws the large "GAME OVER" message at the top
void GGScreen::DrawGameOver()
{
    Graphics graphics(g_hdc);
    FontFamily fontFamily(L"Agency FB");
    SolidBrush brush1(Color(255, 0, 0, 0));
    Font font1(&fontFamily, 96, FontStyleBold, UnitPixel);

    // Measure text width to center it horizontally
    RectF boundingBox;
    RectF layoutRect(0, 0, 1000, 1000);
    graphics.MeasureString(L"GAME OVER", -1, &font1, layoutRect, &boundingBox);

    PointF pos(g_center.x - boundingBox.Width / 2.0f, 50.0f);
    graphics.DrawString(L"GAME OVER", -1, &font1, pos, &brush1);
}

// Draws the player's final score below the game over message
void GGScreen::DrawScore()
{
    Graphics graphics(g_hdc);
    FontFamily fontFamily(L"Agency FB");
    SolidBrush brush1(Color(255, 0, 0, 0));
    Font font1(&fontFamily, 32, FontStyleBold, UnitPixel);

    RectF boundingBox;
    RectF layoutRect(0, 0, 500, 500);

    // Combine label and score as a single string
    std::string strScore = "Your score is: ";
    std::ostringstream oss;
    oss << strScore << score;
    strScore = oss.str();

    // Convert string to wide character for GDI+
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, strScore.c_str(), -1, nullptr, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, strScore.c_str(), -1, &wstr[0], size_needed);
    const WCHAR* wideStr = wstr.c_str();

    // Measure and center the score text
    graphics.MeasureString(wideStr, -1, &font1, layoutRect, &boundingBox);
    PointF pos(g_center.x - boundingBox.Width / 2.0f, 200.0f);
    graphics.DrawString(wideStr, -1, &font1, pos, &brush1);
}

// Draws a triangle that points to the selected button option
void GGScreen::DrawTriangle()
{
    // Offset triangle origin for rotation center alignment
    double trigX = -(_tSize / 3.232);
    double trigY = _tSize / 2;

    // Shift triangle vertically based on current selection
    double buttonYshift = _buttonSize.y * trigYshift + 5 * trigYshift;
    _tPos = { g_center.x - (_buttonSize.x / 2 + 1.5 * _tSize),
              (g_center.y - trigY) + buttonYshift };

    double angle = .0;

    Graphics graphics(g_hdc);
    graphics.ResetTransform();
    graphics.TranslateTransform(_tPos.x - trigX, _tPos.y + trigY);
    graphics.RotateTransform(angle);

    SolidBrush brush(Color(255, 0, 0, 0)); // Black triangle
    PointF triangle[3] = {
        PointF(trigX, -(trigY)),           // Top vertex
        PointF(_tSize + trigX, 0.0f),      // Right vertex
        PointF(trigX, trigY)               // Bottom vertex
    };
    graphics.FillPolygon(&brush, triangle, 3);
}

// Handles keyboard input for navigation and selection
void GGScreen::KeyStates()
{
    static bool isUpButtonPressed = false;
    static bool isDownButtonPressed = false;

    // Up/W key press detection (one-time per press)
    bool isUpPressed = (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000);
    if (!isUpPressed) {
        isUpButtonPressed = false;
    }
    else if (!isUpButtonPressed) {
        --trigYshift;
        isUpButtonPressed = true;
    }

    // Down/S key press detection (one-time per press)
    bool isDownPressed = (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000);
    if (!isDownPressed) {
        isDownButtonPressed = false;
    }
    else if (!isDownButtonPressed) {
        ++trigYshift;
        isDownButtonPressed = true;
    }

    // Clamp selection to 3 buttons: -1 (Play Again), 0 (Shop), 1 (Menu)
    if (trigYshift > 1) trigYshift = -1;
    else if (trigYshift < -1) trigYshift = 1;

    // Enter/Space press detection (edge trigger)
    bool isEnterPressed = (GetAsyncKeyState(VK_RETURN) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8000);
    static bool EnterChanged = false;
    static bool Enter = false;
    if (EnterChanged != isEnterPressed) {
        EnterChanged = isEnterPressed;
        if (!EnterChanged) Enter = true;
    }

    // Action on button select (Play Again or Menu)
    if (Enter) {
        if (trigYshift == 1) {
            g_currentGameState = Menu;   // If "Menu" is selected
        }
        if (trigYshift == -1) {
            g_currentGameState = Reset;  // If "Play Again" is selected
        }
    }
    Enter = false;
}
