#include "framework.h"
#include "WindowsProject1.h"
#include <cmath>
#include <functional>
#include <MMSystem.h>
#include <time.h>
#include <windowsx.h>
#include "KMatrix2.h"
#include "KMatrix3.h"
#include "KTileManager.h"

#include "Gun.h" //Gobals.h 
#include "Enemy.h"
#include "GGScreen.h"
#include "MenuScreen.h"
#include "PauseScreen.h"
#include "Sidekick.h"
#include <iostream>
                                                //Most functions have been moved to utils.h for global access.
#define MAX_LOADSTRING 100                      //Global variables such as vectors, handles, and structs 
                                                //are now declared in globals.h.
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

POINT g_center;
int g_pixelPerUnit = 10;
HWND    g_hwnd = NULL;
HDC     g_hdc = 0;
HBITMAP g_hBitmap = 0;
RECT    g_clientRect;
KTime   g_time;
Image* g_image = nullptr;
Image* g_bulletImage = nullptr;
Image* g_gunImage = nullptr;
int	    g_mouseLButtonDown = 0;
KVector2 g_screenSize = KVector2::zero;
KVector2 g_worldPoint = KVector2::zero;
KVector2 g_mousePos = KVector2::zero;
double g_angle = 0.0;
double g_pi = 0.0;
KTileManager* g_tileManager = nullptr;
KVector2 g_playerPos = KVector2::zero;

// Newly created classes
Gun gun;                // Handles gun drawing and bullet mechanics
Enemy enemy;            // Manages enemies, bullet collision, and animations
GGScreen ggScreen;      // Controls the end-game screen and button logic
MenuScreen menuScreen;  // Displays the main menu
PauseScreen pauseScreen; // Displays the pause screen
Sidekick sidekick;      // Controls AI logic, bullet and knight mechanics,
                        // bullet collisions, and animation/image rendering
GameState g_currentGameState = GameState::Lose; // Tracks the current game state

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HDC hdc);
void OnSize(HWND hwnd);
void Initialize();
void Finalize();
void OnIdle();
void LButtonDown(int x, int y);
void OnLButtonDown(int x, int y);
void OnLButtonUp();
void GameOver();
void GameMenu();
void ScreenPause();

static void InitConsole()
{
    AllocConsole();                                // Create a console window
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);        // Redirect stdout
    freopen_s(&fp, "CONOUT$", "w", stderr);        // Redirect stderr
    freopen_s(&fp, "CONIN$", "r", stdin);          // Redirect stdin
    std::ios::sync_with_stdio();                   // Sync with C++ streams
    std::cout.clear();                             // Clear any error flags
    std::cerr.clear();
    std::cin.clear();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    Initialize();
    //InitConsole();
    DWORD dwOldTime = ::timeGetTime();
    MSG msg;

    //----- available Fonts ------------
    InstalledFontCollection fonts;
    int count = fonts.GetFamilyCount();
    FontFamily* fontFamilies = new FontFamily[count];
    fonts.GetFamilies(count, fontFamilies, &count);

    for (int i = 0; i < count; ++i)
    {
        WCHAR name[LF_FACESIZE];
        fontFamilies[i].GetFamilyName(name);
        wprintf(L"%s\n", name); // Print all available font names
    }

    delete[] fontFamilies;
    // ----------------------------------
    // Main message loop:
    while (true)
    {
        ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
        const DWORD dwNewTime = ::timeGetTime();
        const BOOL bIsTranslateMessage = TranslateAccelerator(msg.hwnd, hAccelTable, &msg);
        if (!bIsTranslateMessage)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }//if

        //60 fps game loop
        g_time.deltaTime = (dwNewTime - dwOldTime) / 1000.0;
        if (dwNewTime - dwOldTime > 1000.0/60.0) {
            OnIdle();

            dwOldTime = dwNewTime;
        }

        if (msg.message == WM_QUIT)
        {
            break;
        }//if
    }//while

    Finalize();
    Gdiplus::GdiplusShutdown(gdiplusToken);

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hwnd = hWnd;
   OnSize(hWnd);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            //OnPaint(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        OnSize(hWnd);
        break;
    case WM_LBUTTONDOWN:
        OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_MOUSEMOVE:
        {
            int x = GET_X_LPARAM(lParam);                          //WM_MOUSEMOVE alows to control gun 
            int y = GET_Y_LPARAM(lParam);                          //while mouse is moving

            g_mousePos.x = x - g_center.x;
            g_mousePos.y = y - g_center.y;

            InverseTransform(&g_mousePos.x, &g_mousePos.y);
            Transform(&g_mousePos.x, &g_mousePos.y);

            if (wParam & MK_LBUTTON) {
                OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); 
            }
        }
        break;
    case WM_LBUTTONUP:
        OnLButtonUp();
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//double(*CALLBACK)(double x)

//--------------------------------------------------------







//--------------------------------------------------------
void OnPaint(HDC hdc)
{
    char buffer[80];


    static double degree = 0.0;
    static double radian = 0.0;
    const double pi = 3.141592;
    const double radianToDegree = 180.0 / pi;
    radian += g_time.deltaTime;
    degree = -radian * radianToDegree;

    KMatrix3 translation;
    KMatrix3 rotation;
    translation.SetTranslation(5,0);
    rotation.SetRotation(radian);
    KVector2 p1 = rotation * translation * KVector2::zero;
    DrawImage(hdc, g_image, p1, degree);

    static int heart_size = 3;
    g_heartAnimator.Draw(hdc, lives, g_screenSize.x - 45 * heart_size, 5, false, heart_size);


    // Draw FPS
    int fps = (int)(1.0 / g_time.deltaTime);

    sprintf_s(buffer, "FPS: %d", fps);
    ::TextOutA(hdc, 1, 1, buffer, (int)strlen(buffer));
    
    sprintf_s(buffer, "Score: %d", score);
    ::TextOutA(hdc, (int)g_center.x - ((int)strlen(buffer) /2)*8, 1, buffer, (int)strlen(buffer));
}

void GameOver()             //Updates screens 
{
    ggScreen.Update();
    ggScreen.Draw();
}

void GameMenu()
{
    menuScreen.Update();
    menuScreen.Draw();
}

void ScreenPause() {
    pauseScreen.Update();
    pauseScreen.Draw();
}                       //---------------------

void OnSize(HWND hwnd)
{
    Finalize();

    ::GetClientRect(g_hwnd, &g_clientRect);
    const int width = g_clientRect.right - g_clientRect.left + 1;
    const int height = g_clientRect.bottom - g_clientRect.top + 1;
    g_screenSize = {width, height};
    g_center.x = width / 2;
    g_center.y = height / 2;
    g_pixelPerUnit = 50;

    HDC hdc = ::GetDC(g_hwnd);
    g_hdc = CreateCompatibleDC(hdc);
    g_hBitmap = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(g_hdc, g_hBitmap);

    Initialize();
}

void Initialize()
{
    srand(time(NULL));
    if (g_image == nullptr)
        g_image = new Image(L"Baren.png");

    if (g_tileManager == nullptr)
        g_tileManager = new KTileManager();
    g_tileManager->LoadTileSheet(L"Atlas-working.png", 16, 32);
                            
    sidekick.Initialize();  //instead of here 
    enemy.Initialize();     //image initialization is 
    gun.Initialize();       //moved to corresponding classes

}//Initialize()

void Finalize()
{
    if (g_tileManager != nullptr) {
        delete g_tileManager;
        g_tileManager = nullptr;
    }
    if (g_hdc != 0) {
        DeleteDC(g_hdc);
        g_hdc = 0;
    }//if
    if (g_hBitmap != 0) {
        DeleteObject(g_hBitmap);
        g_hBitmap = 0;
    }//if
    if (g_image != nullptr) {
        delete g_image;
        g_image = nullptr;
    }//if

    sidekick.Finalize();    //finalization in 
    enemy.Finalize();       //corresponding classes
    gun.Finalize();
}//Finalize()

void UpdateBullets()    //gun class update
{
    gun.Update();
    gun.Draw();
}
void UpdateEnemies()    //enemy class update
{
    enemy.SpawnEnemy();
    enemy.Update();
    enemy.DrawEnemies();
}

void OnIdle()
{
    const int iWidth = g_clientRect.right - g_clientRect.left + 1;
    const int iHeight = g_clientRect.bottom - g_clientRect.top + 1;

    HDC hdc = ::GetDC(g_hwnd);

    HBRUSH brush;
    brush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(g_hdc, brush);
    Rectangle(g_hdc, 0, 0, iWidth, iHeight);

    if (g_currentGameState == GameState::Playing){      //Game is separated into different states
        sidekick.Update();                              //
        sidekick.Draw();                                //based on current state, part of the code 
        UpdateBullets();                                //responsible for that state is called
        UpdateEnemies();
        OnPaint(g_hdc);
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000){      //on ESC pause screen during game
            g_currentGameState = GameState::Pause;
        }
    }
    else if (g_currentGameState == GameState::Lose)     //game over screen
    {
        GameOver();
    }
    else if (g_currentGameState == GameState::Menu)     //menu screen
    {
        GameMenu();
    }
    else if (g_currentGameState == GameState::Reset) {  //instead of going back to gameplay
        bullets.clear();                                //all objects are reset first
        enemies.clear();
        score = 0;
        lives = 3;
        g_currentGameState = GameState::Playing;
    }
    else if (g_currentGameState == GameState::Pause) { //pause screen
        ScreenPause();
    }

    BitBlt(hdc, 0, 0, iWidth, iHeight, g_hdc, 0, 0, SRCCOPY);
    DeleteObject(brush);

    ::ReleaseDC(g_hwnd, hdc);
}//OnIdle()

void LButtonDown(int x, int y)
{
    gun.LoadMag(x, y);
}

void OnLButtonDown(int x, int y)
{
    if (g_mouseLButtonDown != 1) {}
    LButtonDown(x, y);
    g_mouseLButtonDown = 1;
}

void OnLButtonUp()
{
    g_mouseLButtonDown = 0;
}