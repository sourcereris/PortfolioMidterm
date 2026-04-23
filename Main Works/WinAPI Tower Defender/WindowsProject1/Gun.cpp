#include "Gun.h"
#include <iostream>

// ----------- Global Variables ------------
KSpriteAnimator g_heartAnimator;       // Animator for heart (life) icons
std::vector<Bullet> bullets;           // Active bullets in the game


// ----------- Gun Class Implementation ------------

// Constructor: initialize degree and reserve bullet capacity
Gun::Gun() {
    _degree = 0.0;
    bullets.reserve(50);  // Pre-allocate space for bullets
}

Gun::~Gun() {}


// Clean up allocated resources used by the Gun class
void Gun::Finalize() {
    if (g_bulletImage != nullptr) {
        delete g_bulletImage;
        g_bulletImage = nullptr;
    }
    if (g_gunImage != nullptr) {
        delete g_gunImage;
        g_gunImage = nullptr;
    }
    if (_heartTileManager != nullptr) {
        delete _heartTileManager;
        _heartTileManager = nullptr;
    }
}


// Load bullet and gun images, initialize heart (lives) animation
void Gun::Initialize() {
    if (g_bulletImage == nullptr)
        g_bulletImage = new Image(L"bullet.png");

    if (g_gunImage == nullptr)
        g_gunImage = new Image(L"gun.png");

    if (_heartTileManager == nullptr)
        _heartTileManager = new KTileManager();

    _heartTileManager->LoadTileSheet(L"Hearts.png", 42, 12);

    // Configure heart animations for different life counts
    g_heartAnimator.ClearAll();
    g_heartAnimator.SetTilemap(_heartTileManager);
    g_heartAnimator.SetAnimation(3, { KVector2(0, 0) }, 1);
    g_heartAnimator.SetAnimation(2, { KVector2(0, 1) }, 1);
    g_heartAnimator.SetAnimation(1, { KVector2(0, 2) }, 1);
}


// Fires a bullet toward the mouse position at a fixed rate
void Gun::LoadMag(int x, int y) {
    static DWORD oldTime = 0;
    DWORD newTime = ::timeGetTime();
    double shotsPerSecond = 3.0;

    if (newTime - oldTime >= 1000.f / shotsPerSecond) {
        _position.x = x;
        _position.y = y;

        // Convert screen coords to world coords
        InverseTransform(&_position.x, &_position.y);

        if (_position.Length() > 0.00001) {
            Bullet bullet;
            bullet.position = _position.Normalize() * 0.9f;
            bullet.velocity = _position.Normalize() * 2;

            bullets.push_back(bullet);
        }

        oldTime = newTime;
    }
}


// Updates all bullets: moves them and removes those that are out of range
void Gun::Update() {
    const double speed = 6.0;
    double dt = g_time.deltaTime;

    for (auto it = bullets.begin(); it != bullets.end();) {
        it->position = it->position + it->velocity * (float)(speed * dt);

        // Remove bullet if it's too far away
        if (it->position.Length() > 20) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}


// Draws gun and bullets
void Gun::Draw() {
    DrawBullets();
    DrawGun();
}


// Draws all bullets in the world
void Gun::DrawBullets() {
    for (const Bullet& bullet : bullets) {
        DrawImage(g_hdc, g_bulletImage, bullet.position);
    }
}


// Draws the gun, rotated toward the mouse position
void Gun::DrawGun() {
    _degree = atan2(g_mousePos.x, g_mousePos.y) * _radianToDegree;
    KVector2 gunPosition{ 0.f, 0.f };
    DrawImage(g_hdc, g_gunImage, gunPosition, -_degree);
}
