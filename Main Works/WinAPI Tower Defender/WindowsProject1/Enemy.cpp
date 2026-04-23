#include "Enemy.h"

// ----------- Global Variables ------------
std::vector<EnemyBehaviour> enemies;   // List of active enemies
KSpriteAnimator g_enemyAnimator;       // Enemy animation controller
int score = 0;                          // Player score
int lives = 4;                          // Remaining player lives

// Random number generator for enemy spawn direction
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dist(-1.0, 1.0);


// ----------- Enemy Class Implementation ------------

Enemy::Enemy() {
    degree = 0.0;
    enemies.reserve(50);  // Pre-allocate space for enemies
}

Enemy::~Enemy() {}

// Releases resources used by the Enemy class
void Enemy::Finalize() {
    if (g_eTileManager != nullptr) {
        delete g_eTileManager;
        g_eTileManager = nullptr;
    }
}

// Initializes the enemy animation system and tile manager
void Enemy::Initialize() {
    if (g_eTileManager == nullptr)
        g_eTileManager = new KTileManager();

    g_eTileManager->LoadTileSheet(L"enemyAnimation.png", 66, 66);

    g_enemyAnimator.ClearAll();
    g_enemyAnimator.SetTilemap(g_eTileManager);

    std::vector<KVector2> enemyWalk = {
        KVector2(0, 0),
        KVector2(1, 0)
    };
    g_enemyAnimator.SetAnimation(0, enemyWalk, 0.1);  // Walk animation (2 frames)
}

// Spawns a new enemy at a random position on a unit circle every 1/spawnsPerSecond seconds
void Enemy::SpawnEnemy() {
    static DWORD oldTime = 0;
    DWORD newTime = ::timeGetTime();
    double spawnsPerSecond = 6;

    if (newTime - oldTime >= 1000.0 / spawnsPerSecond) {
        _position = { dist(gen), dist(gen) };
        _position = _position.Normalize() * 15;   // Spawn 15 units away from center
        _velocity = _position.Normalize() * -1;   // Move toward center

        EnemyBehaviour enemy;
        enemy.position = _position;
        enemy.velocity = _velocity;

        enemies.push_back(enemy);
        oldTime = newTime;
    }
}

// Updates all enemies' positions and checks for collisions
void Enemy::Update() {
    const double speed = 1;
    double dt = g_time.deltaTime;

    for (auto it = enemies.begin(); it != enemies.end();) {
        it->position = it->position + it->velocity * speed * dt;

        if (it->position.Length() < 0.5) {  // Reached center
            it = enemies.erase(it);
            if (lives > 1)
                --lives;
            else
                g_currentGameState = Lose;
        }
        else if (ChechCollision(it)) {  // Hit by a bullet
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }
}

// Checks if the current enemy was hit by any bullet
bool Enemy::ChechCollision(std::vector<EnemyBehaviour>::iterator& it) {
    double distance;
    if (!bullets.empty()) {
        for (auto itb = bullets.begin(); itb != bullets.end();) {
            distance = sqrt(pow((it->position.x - itb->position.x), 2) +
                pow((it->position.y - itb->position.y), 2));
            if (distance < 0.5) {  // Collision radius threshold
                itb = bullets.erase(itb);
                ++score;
                return true;
            }
            else {
                ++itb;
            }
        }
    }
    return false;
}

// Draws all enemies using the animator and current frame
void Enemy::DrawEnemies() {
    g_enemyAnimator.Update(g_time.deltaTime);
    for (EnemyBehaviour enemy : enemies) {
        Transform(&enemy.position.x, &enemy.position.y);  // Convert to screen coordinates
        g_enemyAnimator.Draw(g_hdc, 0, enemy.position.x - 33, enemy.position.y - 33, false, 1);
    }
}
