#include "hexagon.hpp"

Hexagon::Hexagon(Vector2 position):position(position){}

Hexagon::~Hexagon()
{
}

void Hexagon::draw()
{
    DrawPoly(position, 6, 45, 90, {104, 111, 67, 255});
}

void Hexagon::update()
{
}
