#include "PauseScreen.h"

// Constructor
PauseScreen::PauseScreen() {}

// Destructor
PauseScreen::~PauseScreen() {}

// Called every frame to update key states (e.g., input)
void PauseScreen::Update()
{
    KeyStates();
}

// Called every frame to draw the pause screen UI
void PauseScreen::Draw()
{
    ButtonShift(-1, L"Continue"); // Draw "Continue" button
    ButtonShift(0, L"Menu");      // Draw "Menu" button
    DrawTriangle();               // Draw selection triangle
}

// Draws a button at a shifted position with the given label
void PauseScreen::ButtonShift(int shift, const wchar_t* text)
{
    // Calculate button position based on shift
    double buttonY = g_center.y - _buttonSize.y / 2;
    double buttonX = g_center.x - _buttonSize.x / 2;
    int buttonShift = _buttonSize.y * shift + 5 * shift;

    // Create button rectangle and text position
    KVector2 buttonPosition{ buttonX, buttonY + buttonShift };
    Rect rect(buttonPosition.x, buttonPosition.y, _buttonSize.x, _buttonSize.y); // x, y, width, height
    PointF pointF(g_center.x - _buttonSize.x / 2, buttonPosition.y);

    // Setup graphics tools
    Graphics graphics(g_hdc);
    Pen         pen(Color(255, 0, 0, 0), 2); // Black pen, 2px thickness
    SolidBrush  brush1(Color(255, 0, 0, 0));
    FontFamily  fontFamily(L"Agency FB");
    Font        font(&fontFamily, 24, FontStyleBold, UnitPixel);

    // Draw button and label
    graphics.DrawRectangle(&pen, rect);
    graphics.DrawString(text, -1, &font, pointF, &brush1);
    DrawTitle(); // Draw pause title at top of screen
}

// Draws the selection triangle that indicates current selection
void PauseScreen::DrawTriangle()
{
    // Calculate triangle local offsets
    double trigX = -(_tSize / 3.232); //3.232 centers the triangle
    double trigY = _tSize / 2;

    // Calculate triangle screen position based on selection
    double buttonYshift = _buttonSize.y * trigYshift + 5 * trigYshift;
    _tPos = { g_center.x - (_buttonSize.x / 2 + 1.5 * _tSize), (g_center.y - trigY) + buttonYshift };

    // Setup graphics transform
    double angle = .0;
    Graphics graphics(g_hdc);
    graphics.ResetTransform();
    graphics.TranslateTransform(_tPos.x - trigX, _tPos.y + trigY);
    graphics.RotateTransform(angle);

    // Define triangle points and draw
    SolidBrush brush(Color(255, 0, 0, 0));
    PointF triangle[3] = {
        PointF(trigX, -(trigY)),   // Top
        PointF(_tSize + trigX, 0.0f), // Right
        PointF(trigX, trigY)       // Bottom
    };
    graphics.FillPolygon(&brush, triangle, 3);
}

// Handles user input (W/S or Arrow keys to navigate, Enter/Space to select)
void PauseScreen::KeyStates()
{
    // State variables to prevent multiple triggers per key press
    static bool isUpButtonPressed = false;
    static bool isDownButtonPressed = false;

    // Handle UP or W input
    bool isUpPressed = (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000);
    if (!isUpPressed)
        isUpButtonPressed = false;
    else if (!isUpButtonPressed)
    {
        --trigYshift;
        isUpButtonPressed = true;
    }

    // Handle DOWN or S input
    bool isDownPressed = (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000);
    if (!isDownPressed)
        isDownButtonPressed = false;
    else if (!isDownButtonPressed)
    {
        ++trigYshift;
        isDownButtonPressed = true;
    }

    // Clamp selection index to valid range (-1 = Continue, 0 = Menu)
    if (trigYshift > 0) trigYshift = -1;
    else if (trigYshift < -1) trigYshift = 0;

    // Handle ENTER or SPACE input for confirmation
    bool isEnterPressed = (GetAsyncKeyState(VK_RETURN) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8000);
    static bool EnterChanged = false;
    static bool Enter = false;
    if (EnterChanged != isEnterPressed) {
        EnterChanged = isEnterPressed;
        if (!EnterChanged) Enter = true;
    }

    // Perform action based on selected option
    if (Enter) {
        if (trigYshift == 0)          // If "Menu" is selected
            g_currentGameState = Menu;
        else if (trigYshift == -1)    // If "Continue" is selected
            g_currentGameState = Playing;
    }
    Enter = false;
}

// Draws the title text "PAUSE" at the top of the screen
void PauseScreen::DrawTitle()
{
    Graphics graphics(g_hdc);
    FontFamily  fontFamily(L"Agency FB");
    SolidBrush  brush1(Color(255, 0, 0, 0));
    Font        font1(&fontFamily, 96, FontStyleBold, UnitPixel);

    RectF boundingBox;
    RectF layoutRect(0, 0, 1000, 1000);
    graphics.MeasureString(L"PAUSE", -1, &font1, layoutRect, &boundingBox);

    PointF pos(g_center.x - boundingBox.Width / 2.0f, 50.0f); // Center the title
    graphics.DrawString(L"PAUSE", -1, &font1, pos, &brush1);
}
