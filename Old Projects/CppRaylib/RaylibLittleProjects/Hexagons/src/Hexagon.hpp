#pragma once
#include <raylib.h>

class Hexagon{
    public:
        Hexagon(Vector2 position);
        ~Hexagon();
        void draw();
        void update();
            bool operator<(const Hexagon& other) const {
        if (position.x != other.position.x)
            return position.x < other.position.x;
        return position.y < other.position.y;
    }
    private:
        Vector2 position;
};