## Project 2 – Simple 3D shooter using PyOpenGL

Small Python-based 3D demo built with Pygame and PyOpenGL that showcases basic rendering, camera control, and simple gameplay elements

**Key features**

- OpenGL sets up smooth lighting, spheres for enemies and bullets.
- Enemies spawn at random points on a surrounding sphere and moves inward; left-click shoots Bullet instances heading straight from the camera, which travel forward and collide with enemies to remove them.
- Free-look camera system, mouse-driven yaw/pitch rotation and keyboard-controlled elevation and orbit path in the Camera class.
- Physics-inspired motion, applying an inverse-distance gravitational pull from a central “Sun” object to floating shells (mass, force constant, integration).
- Modular code organization, with clear separation across Main, Camera, Sun, Enemy, Gun, Bullet, RandomPos, LoadMesh, and Mesh components.

https://github.com/user-attachments/assets/1369adba-717b-404f-9d4d-4699302cb8c3
