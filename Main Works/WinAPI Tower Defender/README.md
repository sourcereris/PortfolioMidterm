## KNIGHTFALL

https://github.com/user-attachments/assets/712f20d2-3c2e-4a22-a12f-fa8de980eaa8

### About This Project

This is a fast-paced 2D arcade shooter built entirely from scratch in C++. It uses the Windows API (WinAPI) for all window creation and input handling, and GDI+ for all 2D graphics rendering. No external game engine was used.

The goal is to defend the center from waves of enemies. The player controls the central gun with the mouse, while an AI-controlled "Sidekick" knight automatically moves and attacks nearby enemies.

**Technical Features**

This project was a deep dive into the low-level fundamentals of a 2D game. All systems were built from the ground up, including:

- **Core Technology**: Built in C++ using only the native WinAPI and GDI+ libraries.

- **Custom Game Loop**: A fixed 60 FPS game loop responsible for all update, render, and input logic.

- **Object-Oriented Design**: Game logic is fully encapsulated into classes, including Gun, Enemy, and the Sidekick.

- **Custom Sprite Animation System**:

  - A KTileManager class loads .png sprite sheets and manages tile data.

  - A KSpriteAnimator class handles frame-by-frame animation, timing, scaling, and horizontal mirroring (used by the Sidekick and Enemies).

- **AI Companion**: The Sidekick (knight) is an autonomous AI agent that automatically identifies the nearest enemy, moves toward it, and fires its own bullets.

- **Game State Management**: A state machine (using the GameState enum) controls the application flow between the Main Menu, Playing, Pause, and Game Over screens.

- **Physics and Collision**: All game logic, including bullet-enemy collision detection, enemy spawning, and movement (velocity/position updates), was implemented from scratch.
