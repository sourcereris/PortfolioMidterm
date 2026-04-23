#include "Sidekick.h"

//----------- globals ------------

// Vector storing all active bullets fired by the sidekick
std::vector<SidekickBehaviour> SKbullets;

// The single sidekick instance (referred to as the "knight")
SidekickBehaviour _knight;

// Random number generator setup for bullet spread (adds slight randomness to bullet direction)
std::random_device rd1;
std::mt19937 gen1(rd1());
std::uniform_real_distribution<double> dist1(-0.3, 0.3);

// Global angle for aiming/shooting direction
double degree = 0;
double superSayan = 0;
// Used to determine if sprite animation should be mirrored (flipped horizontally)
bool mirrorAnimation = false;

// Constructor: initializes sidekick position to the center of the screen
Sidekick::Sidekick() {
    _knight.position.x = (double)g_center.x;
    _knight.position.y = (double)g_center.y;
}

// Destructor: empty because cleanup is handled in Finalize()
Sidekick::~Sidekick() {}

// Cleans up allocated resources (image and tile manager)
void Sidekick::Finalize() {
    if (_bulletImage != nullptr) {
        delete _bulletImage;
        _bulletImage = nullptr;
    }
    if (_sidekickTileManager != nullptr) {
        delete _sidekickTileManager;
        _sidekickTileManager = nullptr;
    }
}

// Initializes sidekick graphics and animations
void Sidekick::Initialize() {
    // Load bullet image if not already loaded
    if (_bulletImage == nullptr)
        _bulletImage = new Image(L"bullet1.png");

    // Load the tilemap for animations
    if (_sidekickTileManager == nullptr)
        _sidekickTileManager = new KTileManager();
    _sidekickTileManager->LoadTileSheet(L"Atlas-working.png", 16, 32);

    // Set up animation frames (e.g., walking right)
    _animator.ClearAll();
    _animator.SetTilemap(_sidekickTileManager);
    std::vector<KVector2> walkRightFrames = {
        KVector2(0, 0),
        KVector2(1, 0),
        KVector2(2, 0),
        KVector2(3, 0)
    };
    _animator.SetAnimation(0, walkRightFrames, 0.15); // Animation 0 plays with a speed of 0.15
}

// Called every frame to update animation, movement, and bullets
void Sidekick::Update() {
    _animator.Update(g_time.deltaTime); // Update animation timer
    MoveTo();      // Move towards enemy
    Shoot();       // Possibly fire a bullet
    UpdateBullets(); // Update all bullets
}

// Called every frame to render the sidekick and its bullets
void Sidekick::Draw() {
    DrawBullets(); // Draw bullets first (behind the character)

    // Convert game world coordinates to screen space
    double x = _knight.position.x;
    double y = _knight.position.y;
    Transform(&x, &y);

    // Draw sidekick animation at the transformed position
    _animator.Draw(g_hdc, 0, x - 16, y - 48, mirrorAnimation, 2.0); // Draw at 2x scale
}

// Moves the sidekick toward the first enemy in the list
void Sidekick::MoveTo() {
    const double speed = 2.5;
    double dt = g_time.deltaTime;

    // If there are enemies, move toward the first one
    KVector2 avg = KVector2::zero;
    if (enemies.size() != 0) {
        avg.x = enemies.at(0).position.x;
        avg.y = enemies.at(0).position.y;
    }
    else return;

    // Compute angle and velocity vector toward enemy
    double x = avg.x - _knight.position.x;
    double y = avg.y - _knight.position.y;
    degree = atan2(y, x);

    _knight.velocity.x = cos(degree) / 2;
    _knight.velocity.y = sin(degree) / 2;

    // Update position
    _knight.position += _knight.velocity * speed * dt;

    // Flip animation based on direction
    mirrorAnimation = (_knight.velocity.x < 0);
}

// Shoots a bullet every 1.5 times per second with slight direction variation
void Sidekick::Shoot() {
    static DWORD oldTime = 0;
    DWORD newTime = ::timeGetTime();
    double shotsPerSecond = 2;

    // Fire a bullet if enough time has passed
    if (newTime - oldTime >= 1000.f / shotsPerSecond) {
        KVector2 position = _knight.position;
        SidekickBehaviour bullet;
        bullet.bulletInitialPosition = position;
        bullet.position = position;

        // Add random spread to the shooting direction
        degree += dist1(gen1);
        bullet.velocity.x = cos(degree);
        bullet.velocity.y = sin(degree);

        SKbullets.push_back(bullet); // Add bullet to list

        oldTime = newTime; // Reset cooldown timer
    }

}

// Draws all currently active bullets
void Sidekick::DrawBullets() {
    for (auto it = SKbullets.begin(); it != SKbullets.end(); ++it) {
        DrawImage(g_hdc, _bulletImage, it->position);
    }
}

// Updates bullet positions and removes those too far or hitting enemies
void Sidekick::UpdateBullets() {
    const double speed = 4.0;
    double dt = g_time.deltaTime;

    for (auto it = SKbullets.begin(); it != SKbullets.end();) {
        // Move bullet
        it->position = it->position + it->velocity * speed * dt;

        // Compute distance from initial position
        double distance = sqrt(pow((it->position.x - it->bulletInitialPosition.x), 2) +
            pow((it->position.y - it->bulletInitialPosition.y), 2));

        // Remove bullet if too far or it collided with an enemy
        if (distance > 10) it = SKbullets.erase(it);
        else if (CollisionWithEnemy(it)) it = SKbullets.erase(it);
        else ++it;
    }
}

// Checks if a bullet has collided with any enemy
bool Sidekick::CollisionWithEnemy(std::vector<SidekickBehaviour>::iterator& it) {
    if (!enemies.empty()) {
        for (auto itb = enemies.begin(); itb != enemies.end();) {
            // Compute distance between bullet and enemy
            double distance = sqrt(pow((it->position.x - itb->position.x), 2) +
                pow((it->position.y - itb->position.y), 2));
            if (distance < 0.5) {
                itb = enemies.erase(itb); // Remove enemy
                ++score; // Increase score
                return true;
            }
            else {
                ++itb;
            }
        }
    }
    return false;
}
